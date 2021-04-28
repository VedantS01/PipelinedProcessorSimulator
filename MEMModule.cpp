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
        buf.ready = true;
        ready = true;
        return buf;
    }
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
        cout << "Loaded data " << d << " in register " << buf.dest << endl;
    }
    else if (emBuf.store)
    {
        buf.load = false;
        buf.aluInstr = false;
        //here, emBuf.aluOut is m address and emBuf.dest is register contents
        D$.write(emBuf.aluOutput, emBuf.dest);
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
    else 
    {
        cout << "Can't reach here, logical error.\n";
    }
    buf.invalid = false;
    buf.ready = true;
    ready = true;
    return buf;
}