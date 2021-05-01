/**
 *  IDRFModule.cpp  :       Implements the class IDRFModule
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Saboo, CS19B074
 * 
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

int signExtend(int x, int s)
{
    return ((s << 7) | (s << 6) | (s << 5) | (s << 4) | x);
}

IDEXBuffer IDRFModule::execute()
{
    //decode here
    IDEXBuffer buf;
    if (ifidBuf.invalid)
    {
        buf.invalid = true;
        //buf.ready = true;
        ready = true;
        return buf;
    }
    int instruction = ifidBuf.getInstruction();
    buf.npc = ifidBuf.getNPC();
    int opcode = instruction >> 12;
    int mode = opcode >> 2;
    int subop = opcode & 3;
    if (mode == 0)
    {
        buf.arithmetic = true;
        buf.logical = false;
        buf.load = false;
        buf.jump = false;
        buf.bneq = false;
        buf.store = false;
        buf.subop = subop;
        rf.getBusy();
        rf.reset();
        int destA = (instruction >> 8) & 0xf;
        int src1A = (instruction >> 4) & 0xf;
        int src2A = instruction & 0xf;
        if (subop == 3)
        {
            buf.src1 = registerFetch(destA);
#ifdef RENAMING
            buf.src1.tag = RENAME;
            RENAME++;
#endif
            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.src1.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            buf.dest.tag = destA;
            buf.dest.valid = false; //it will overwritten

            FU.renderInvalidIfValid(destA);
        }
        else
        {
            buf.src2 = registerFetch(src2A);
            buf.src1 = registerFetch(src1A);
#ifdef RENAMING
            buf.src1.tag = RENAME;
            RENAME++;
#endif
#ifdef RENAMING
            buf.src2.tag = RENAME;
            RENAME++;
#endif
            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.src1.valid) || (!buf.src2.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }

            buf.dest.tag = destA;
            buf.dest.valid = false;

            // if(src1A == destA)
            // {
            //     buf.src1.valid = false;
            // }
            // if(src2A == destA)
            // {
            //     buf.src2.valid = false;
            // }
            
            FU.renderInvalidIfValid(destA);
        }

        rf.isWriting[destA] ++;
    }
    else if (mode == 1)
    {
        buf.logical = true;
        buf.arithmetic = false;
        buf.load = false;
        buf.jump = false;
        buf.bneq = false;
        buf.store = false;
        buf.subop = subop;
        rf.getBusy();
        rf.reset();
        int destA = (instruction >> 8) & 0xf;
        int src1A = (instruction >> 4) & 0xf;
        int src2A = instruction & 0xf;

        //register fetch
        //fetch dest


        if (subop == 2)
        {
            buf.src1 = registerFetch(src1A);

            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.src1.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }

            buf.src2.valid = false;

            buf.dest.tag = destA;
            buf.dest.valid = false;
            
            // if(src1A == destA)
            // {
            //     buf.validsrc1 = false;
            // }

            // FU.renderInvalidIfValid(destA);
        }
        else
        {
            buf.src2 = registerFetch(src2A);
            buf.src1 = registerFetch(src1A);
#ifdef RENAMING
            buf.src1.tag = RENAME;
            RENAME++;
#endif
#ifdef RENAMING
            buf.src2.tag = RENAME;
            RENAME++;
#endif
            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.src1.valid) || (!buf.src2.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }

            buf.dest.tag = destA;
            buf.dest.valid = false;

            // if(src1A == destA)
            // {
            //     buf.src1.valid = false;
            // }
            // if(src2A == destA)
            // {
            //     buf.src2.valid = false;
            // }
            
            FU.renderInvalidIfValid(destA);
        }
        rf.isWriting[destA]++;
    }
    else if (mode == 2)
    {
        if (subop == 0)
        {
            //load
            buf.logical = false;
            buf.arithmetic = false;
            buf.load = true;
            buf.jump = false;
            buf.bneq = false;
            buf.store = false;
            rf.getBusy();
            rf.reset();
            int destA = (instruction >> 8) & 0xf;
            int src1A = (instruction >> 4) & 0xf;
            int src2A = instruction & 0xf;
            //base register
            buf.src1 = registerFetch(src1A);

            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.src1.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }

            //src2 is invalid
            buf.src2.valid = false;

            //load will write in dest
            buf.dest.tag = destA;
            buf.dest.valid = false;
            
            // if(src1A == destA)
            // {
            //     buf.validsrc1 = false;
            // }
            
            FU.renderInvalidIfValid(destA);

            rf.isWriting[destA]++;

            //offset will be given in src2A
            int s = src2A >> 3;
            buf.offset = signExtend(src2A, s);
        }
        else if (subop == 1)
        {
            //store
            buf.store = true;
            buf.logical = false;
            buf.arithmetic = false;
            buf.load = false;
            buf.jump = false;
            buf.bneq = false;
            rf.getBusy();
            rf.reset();
            int destA = (instruction >> 8) & 0xf;
            int src1A = (instruction >> 4) & 0xf;
            int src2A = instruction & 0xf;

            //base register
            buf.src1 = registerFetch(src1A);

            //src2 is invalid
            buf.src2.valid = false;

            //register to be stored
            buf.dest = registerFetch(destA);
            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.src1.valid) || (!buf.dest.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }

            //offset will be given in src2A
            int s = src2A >> 3;
            buf.offset = signExtend(src2A, s);
        }
        else if (subop == 2)
        {
            buf.jump_addr = (instruction >> 4) & 0xff;
            buf.store = false;
            buf.logical = false;
            buf.arithmetic = false;
            buf.load = false;
            buf.jump = true;
            buf.bneq = false;
            //branch issues;

            // ready = false;
            // buf.invalid = false;
            // ifidBuf.invalid = true;
            // return buf;
            // // BRANCH = 2;
        }
        else
        {
            buf.jump_addr = instruction & 0xff;
            buf.store = false;
            buf.logical = false;
            buf.arithmetic = false;
            buf.load = false;
            buf.jump = false;
            buf.bneq = true;
            int destA = (instruction >> 8) & 0xf;
            rf.getBusy();
            rf.reset();
            
            buf.dest = registerFetch(destA);
            if(!ENABLE_OPEARND_FORWARDING)
            {
                if((!buf.dest.valid))
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }

        }
    }
    else if (mode == 3)
    {
        //issue halt signal
        buf.HALT_SIGNAL = true;
        buf.invalid = false;
        ready = false;
        ifidBuf.invalid = true;
        return buf;
    }
    buf.invalid = false;
    ready = true;
    return buf;
}

bool IDRFModule::resolveBranch(int reg)
{
    return (reg == rf.read(0));
}

RS IDRFModule::registerFetch(int tag) {
    //fetch tag
    RS rs;
    rs.tag = tag;
    if(rf.isWriting[tag] != 0)
    {
        if(ENABLE_OPEARND_FORWARDING)
        {
            int tval = FU.request(tag);
            if(FU.request_success)
            {
                rs.data = tval;
                rs.valid = true;
            }
            else
            {
                rs.valid = false;
            }
        }
        else
        {
            rs.valid = false;
        }
    }
    else
    {
        rs.data = rf.read(tag);
        rs.valid = true;
    }
    return rs;
}
