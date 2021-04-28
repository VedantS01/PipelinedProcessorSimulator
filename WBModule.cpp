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
    if (mwBuf.aluInstr)
    {
        rf.write(mwBuf.dest, mwBuf.val);
        rf.isWriting[mwBuf.dest] = false;
        cout << "Written in reg-write: " << mwBuf.val << " on register " << mwBuf.dest << endl; 
    }
    else if (mwBuf.load)
    {
        rf.write(mwBuf.dest, mwBuf.lmd);
        rf.isWriting[mwBuf.dest] = false;
        cout << "Written: " << mwBuf.lmd << " on register " << mwBuf.dest << endl;
    }
    status.invalid = false;
    status.ready = true;
    ready = true;
    return status;
}