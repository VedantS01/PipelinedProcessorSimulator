/**
 *  MEMModule.cpp   :       Implements the class MEMModule
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

MWBuffer MEMModule::execute()
{
    MWBuffer buf;
    
    if (emBuf.invalid)
    {
        buf.invalid = true;
        ready = true;
        return buf;
    }

    cout << "MEM: " << emBuf.npc << endl;
    buf.npc = emBuf.npc;
    if (emBuf.load)
    {
        buf.load = true;
        buf.aluInstr = false;
        int d = D$.request(emBuf.aluOutput);
        //if no error
        LMD.write(d);
        buf.lmd = d;
        buf.dest = emBuf.dest;
        buf.destval = d;
        buf.validdest = true;
    }
    else if (emBuf.store)
    {
        buf.load = false;
        buf.aluInstr = false;
        //here, emBuf.aluOut is m address and emBuf.dest is register contents
        D$.write(emBuf.aluOutput, emBuf.destval);
    }
    else if(emBuf.writeToRegister)
    {
        buf.aluInstr = true;
        buf.load = false;
        buf.dest = emBuf.dest;
        buf.destval = emBuf.aluOutput;
        buf.validdest = true;
        buf.val = emBuf.aluOutput;
    }
    else if(emBuf.HALT_SIGNAL)
    {
        buf.HALT_SIGNAL = true;
        buf.invalid = false;
        ready = false;
        return buf;
    } 
    else 
    {
        cerr << "Can't reach here, logical error.\n";
    }
    buf.invalid = false;
    ready = true;
    return buf;
}