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

IDEXBuffer IDRFModule::execute()
{
    //decode here
    IDEXBuffer buf;
    if (ifidBuf.invalid)
    {
        buf.invalid = true;
        return buf;
    }
    int instruction = ifidBuf.getInstruction();
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
        if (rf.isWriting[src2A] || rf.isWriting[src1A])
        {
            stall[0] = true;

            stall[1] = true;
            buf.invalid = true;
            return buf;
        }
        buf.src2 = rf.read(src2A);
        buf.src1 = rf.read(src1A);
        buf.dest = destA;
        rf.isWriting[buf.dest] = true;
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
        if (rf.isWriting[src2A] || rf.isWriting[src1A])
        {
            stall[0] = true;

            stall[1] = true;
            buf.invalid = true;
            return buf;
        }
        buf.src2 = rf.read(src2A);
        buf.src1 = rf.read(src1A);
        buf.dest = destA;
        rf.isWriting[buf.dest] = true;
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
                return buf;
            }
            int s = src2A >> 3;
            buf.src2 = signExtend(src2A, s);
            buf.src1 = rf.read(src1A);
            buf.dest = destA;
            rf.isWriting[buf.dest] = true;
        }
        else if (subop == 1)
        {
            buf.store = true;
            rf.getBusy();
            rf.reset();
            int destA = (instruction >> 8) & 0xf;
            int src1A = (instruction >> 4) & 0xf;
            int src2A = instruction & 0xf;
            int s = src2A >> 3;
            buf.src2 = signExtend(src2A, s);
            buf.src1 = rf.read(src1A);
            buf.dest = destA;
            if (rf.isWriting[src1A])
            {
                stall[0] = true;
                stall[1] = true;
                buf.invalid = true;
                return buf;
            }
        }
        else if (subop == 2)
        {
            buf.addr = (instruction >> 4) & 0xff;
            buf.jump = true;
            stall[0] = true;
            stall[1] = true;
            //branch issues;
        }
        else
        {
            buf.addr = instruction & 0xff;
            int destA = (instruction >> 8) & 0xf;
            rf.getBusy();
            rf.reset();
            int dest = rf.read(destA);
            buf.jump = resolveBranch(dest);
            buf.dest = dest;
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
    return buf;
}

int signExtend(int x, int s)
{
    return ((s << 7) | (s << 6) | (s << 5) | (s << 4) | x);
}

bool IDRFModule::resolveBranch(int reg)
{
    return (reg == rf.read(0));
}
