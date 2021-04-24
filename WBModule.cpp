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

void WBModule::execute()
{
    if (mwBuf.aluInstr)
    {
        rf.write(mwBuf.dest, mwBuf.val);
    }
    else if (mwBuf.load)
    {
        rf.write(mwBuf.dest, mwBuf.lmd);
    }
}