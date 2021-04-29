/**
 *  WBModule.cpp    :       Implements the class WBModule
 * 
 *  Version         :       1.0
 *  Author          :       Sanchit Gupta
 * 
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

WBSTATUS WBModule::execute()
{
    WBSTATUS status;
    if (mwBuf.invalid)
    {
        status.invalid = true;
        status.ready = true;
        ready = true;
        return status;
    }
    if (mwBuf.aluInstr)
    {
        if(rf.isWriting[mwBuf.dest] == 0)
        {
            cout << "rf error" << endl;
        }
        if(rf.isWriting[mwBuf.dest] == 1)
        {
            rf.write(mwBuf.dest, mwBuf.destval);
        }
        rf.isWriting[mwBuf.dest]--;
    }
    else if (mwBuf.load)
    {
        if(rf.isWriting[mwBuf.dest] == 0)
        {
            cout << "rf error" << endl;
        }
        if(rf.isWriting[mwBuf.dest] == 1)
        {
            rf.write(mwBuf.dest, mwBuf.lmd);
        }
        rf.isWriting[mwBuf.dest]--;
    }
    else if (mwBuf.HALT_SIGNAL)
    {
        status.invalid = false;
        status.ready = false;
        ready = false;
        mwBuf.invalid = true;
        return status;
    }
    status.invalid = false;
    status.ready = true;
    ready = true;
    return status;
}