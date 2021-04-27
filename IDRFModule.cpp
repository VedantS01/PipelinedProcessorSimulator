/**
 *  IDRFModule.cpp  :       Implements the class IFModule
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Saboo
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
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
        buf.ready = true;
        return buf;
    }
    int instruction = ifidBuf.getInstruction();
    cout << "Instruction: " << instruction << endl;
    int opcode = instruction >> 12;
    int mode = opcode >> 2;
    int subop = opcode & 3;
    if (mode == 0)
    {
        buf.arithmetic = 1;
        buf.subop = subop;
        rf.getBusy();
        rf.reset();
        int destA = (instruction >> 8) & 0xf;
        int src1A = (instruction >> 4) & 0xf;
        int src2A = instruction & 0xf;
        if(subop == 3) {
            if (rf.isWriting[destA])
            {
                stall[0] = true;
                stall[1] = true;
                buf.invalid = true;
                buf.ready = false;
                return buf;
            }
            buf.validsrc1 = false;
        
            buf.validsrc2 = false;

            buf.dest = destA;
            buf.destval = rf.read(destA);
            buf.validdest = false; //it will overwritten
        } else {
            if (rf.isWriting[src2A] || rf.isWriting[src1A])
            {
                stall[0] = true;
                stall[1] = true;
                buf.invalid = true;
                buf.ready = false;
                return buf;
            }
            buf.src1 = src1A;
            buf.srcval1 = rf.read(src1A);
            buf.validsrc1 = true;
        
            buf.src2 = src2A;
            buf.srcval2 = rf.read(src2A);
            buf.validsrc2 = true;

            buf.dest = destA;
            buf.validdest = false;
        }
        
        rf.isWriting[destA] = true;
    }
    else if (mode == 1)
    {
        buf.logical = 1;
        buf.subop = subop;
        rf.getBusy();
        rf.reset();
        int destA = (instruction >> 8) & 0xf;
        int src1A = (instruction >> 4) & 0xf;
        int src2A = instruction & 0xf;
        if(subop == 2) {
            if (rf.isWriting[destA] || rf.isWriting[src1A])
            {
                stall[0] = true;
                stall[1] = true;
                buf.invalid = true;
                buf.ready = false;
                return buf;
            }
            buf.src1 = src1A;
            buf.srcval1 = rf.read(src1A);
            buf.validsrc1 = true;
        
            buf.validsrc2 = false;

            buf.dest = destA;
            buf.validdest = false;
        } else {
            if (rf.isWriting[src2A] || rf.isWriting[src1A])
            {
                stall[0] = true;
                stall[1] = true;
                buf.invalid = true;
                buf.ready = false;
                return buf;
            }
            buf.src1 = src1A;
            buf.srcval1 = rf.read(src1A);
            buf.validsrc1 = true;
        
            buf.src2 = src2A;
            buf.srcval2 = rf.read(src2A);
            buf.validsrc2 = true;

            buf.dest = destA;
            buf.validdest = false;
        }
        rf.isWriting[destA] = true;
    }
    else if (mode == 2)
    {
        if (subop == 0)
        {
            buf.load = true;
            rf.getBusy();
            rf.reset();
            int destA = (instruction >> 8) & 0xf;
            int src1A = (instruction >> 4) & 0xf;
            int src2A = instruction & 0xf;
            if (rf.isWriting[src1A])
            {
                stall[0] = true;

                stall[1] = true;
                buf.invalid = true;
                buf.ready = false;
                return buf;
            }
            //base register
            buf.src1 = src1A;
            buf.srcval1 = rf.read(src1A);
            buf.validsrc1 = true;
        
            //src2 is invalid
            buf.validsrc2 = false;

            //load will write in dest
            buf.dest = destA;
            buf.validdest = false;
            rf.isWriting[destA] = true;

            //offset will be given in src2A
            int s = src2A >> 3;
            buf.offset = signExtend(src2A, s);
        }
        else if (subop == 1)
        {
            buf.store = true;
            rf.getBusy();
            rf.reset();
            int destA = (instruction >> 8) & 0xf;
            int src1A = (instruction >> 4) & 0xf;
            int src2A = instruction & 0xf;
            if (rf.isWriting[src1A] || rf.isWriting[destA])
            {
                stall[0] = true;

                stall[1] = true;
                buf.invalid = true;
                buf.ready = false;
                return buf;
            }
            //base register
            buf.src1 = src1A;
            buf.srcval1 = rf.read(src1A);
            buf.validsrc1 = true;
        
            //src2 is invalid
            buf.validsrc2 = false;

            //store will read from dest
            buf.dest = destA;
            buf.destval = rf.read(destA);
            buf.validdest = true;

            //offset will be given in src2A
            int s = src2A >> 3;
            buf.offset = signExtend(src2A, s);
        }
        else if (subop == 2)
        {
            buf.jump_addr = (instruction >> 4) & 0xff;
            buf.jump = true;
            stall[0] = true;
            stall[1] = true;
            //branch issues;
        }
        else
        {
            buf.jump_addr = instruction & 0xff;
            buf.bneq = true;
            int destA = (instruction >> 8) & 0xf;
            rf.getBusy();
            rf.reset();
            int dest = rf.read(destA);
            //buf.jump = resolveBranch(dest);
            buf.dest = destA;
            buf.destval = dest;
            buf.validdest = true;
            stall[0] = true;
            stall[1] = true;
        }
    }
    else if (mode == 3)
    {
        //issue halt signal
        buf.HALT_SIGNAL = true;
    }
    buf.invalid = false;
    buf.ready = true;
    return buf;
}

bool IDRFModule::resolveBranch(int reg)
{
    return (reg == rf.read(0));
}
