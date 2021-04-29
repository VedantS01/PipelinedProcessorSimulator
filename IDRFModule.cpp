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
            if (rf.isWriting[destA] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(destA);
                    if(FU.request_success)
                    {
                        buf.destval = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.destval = rf.read(destA);
            }
            buf.validsrc1 = false;

            buf.validsrc2 = false;

            buf.dest = destA;
            buf.validdest = false; //it will overwritten

            FU.renderInvalidIfValid(destA);
        }
        else
        {
            if (rf.isWriting[src2A] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src2A);
                    if(FU.request_success)
                    {
                        buf.srcval2 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval2 = rf.read(src2A);
            }
            if (rf.isWriting[src1A])
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src1A);
                    if(FU.request_success)
                    {
                        buf.srcval1 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval1 = rf.read(src1A);
            }
            buf.src1 = src1A;
            buf.validsrc1 = true;

            buf.src2 = src2A;
            buf.validsrc2 = true;

            buf.dest = destA;
            buf.validdest = false;

            if(src1A == destA)
            {
                buf.validsrc1 = false;
            }
            if(src2A == destA)
            {
                buf.validsrc2 = false;
            }
            
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
        if (subop == 2)
        {
            if (rf.isWriting[src1A] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src1A);
                    if(FU.request_success)
                    {
                        buf.srcval1 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval1 = rf.read(src1A);
            }
            buf.src1 = src1A;
            buf.validsrc1 = false;

            buf.validsrc2 = false;

            buf.dest = destA;
            buf.validdest = false;
            
            if(src1A == destA)
            {
                buf.validsrc1 = false;
            }

            // FU.renderInvalidIfValid(destA);
        }
        else
        {
            if (rf.isWriting[src2A] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src2A);
                    if(FU.request_success)
                    {
                        buf.srcval2 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval2 = rf.read(src2A);
            }
            if (rf.isWriting[src1A] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src1A);
                    if(FU.request_success)
                    {
                        buf.srcval1 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval1 = rf.read(src1A);
            }
            buf.src1 = src1A;
            buf.validsrc1 = false;

            buf.src2 = src2A;
            buf.validsrc2 = false;

            buf.dest = destA;
            buf.validdest = false;
            
            if(src1A == destA)
            {
                buf.validsrc1 = false;
            }
            if(src2A == destA)
            {
                buf.validsrc2 = false;
            }
            
            // FU.renderInvalidIfValid(destA);
        }
        rf.isWriting[destA]++;
    }
    else if (mode == 2)
    {
        if (subop == 0)
        {
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
            if (rf.isWriting[src1A] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src1A);
                    if(FU.request_success)
                    {
                        buf.srcval1 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval1 = rf.read(src1A);
            }
            //base register
            buf.src1 = src1A;
            buf.validsrc1 = false;

            //src2 is invalid
            buf.validsrc2 = false;

            //load will write in dest
            buf.dest = destA;
            buf.validdest = false;
            
            if(src1A == destA)
            {
                buf.validsrc1 = false;
            }
            
            // FU.renderInvalidIfValid(destA);

            rf.isWriting[destA]++;

            //offset will be given in src2A
            int s = src2A >> 3;
            buf.offset = signExtend(src2A, s);
        }
        else if (subop == 1)
        {
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
            if (rf.isWriting[destA] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(destA);
                    if(FU.request_success)
                    {
                        buf.destval = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.destval = rf.read(destA);
            }
            if (rf.isWriting[src1A] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(src1A);
                    if(FU.request_success)
                    {
                        buf.srcval1 = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.srcval1 = rf.read(src1A);
            }
            
            //base register
            buf.src1 = src1A;
            buf.validsrc1 = false;

            //src2 is invalid
            buf.validsrc2 = false;

            //store will read from dest
            buf.dest = destA;
            buf.validdest = false;

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
            if (rf.isWriting[destA] != 0)
            {
                if(ENABLE_OPEARND_FORWARDING)
                {
                    int tval = FU.request(destA);
                    if(FU.request_success)
                    {
                        buf.destval = tval;
                    }
                    else
                    {
                        total_stalls++;
                        data_stalls++;
                        buf.invalid = true;
                        ready = false;
                        return buf;
                    }
                }
                else
                {
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
            {
                buf.destval = rf.read(destA);
            }
            
            buf.dest = destA;
            buf.validdest = false;

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
