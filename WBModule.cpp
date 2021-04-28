/**
 *  MEMModule.cpp   :       Implements the class WBModule
 * 
 *  Version         :       1.0
 *  Author          :       Sanchit Gupta
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
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
    cout << "WB:" << mwBuf.npc << endl;
    if (mwBuf.aluInstr)
    {
        rf.write(mwBuf.dest, mwBuf.destval);
        /*
        if(rf.request_failed)
        {
            status.invalid = true;
            status.ready = false;
            ready = false;
            rf.reset();
            return status;
        }
        */
        rf.isWriting[mwBuf.dest] = false;
        cout << "Written " << mwBuf.destval << " on reg " << mwBuf.dest << endl;
    }
    else if (mwBuf.load)
    {
        rf.write(mwBuf.dest, mwBuf.lmd);
        rf.isWriting[mwBuf.dest] = false;
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