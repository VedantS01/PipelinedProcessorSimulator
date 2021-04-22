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

MWBuffer MEMModule::execute() {
    MWBuffer buf;
    if(emBuf.load) {
        int d = D$.request(emBuf.aluOutput);
        //if no error
        LMD.write(d);
    } else if(emBuf.store) {
        //here, emBuf.aluOut is m address and emBuf.dest is register contents
        D$.write(emBuf.aluOutput, emBuf.dest);
    }
    return buf;
}