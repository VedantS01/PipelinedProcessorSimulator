/**
 *  IFModule.cpp    :       Implements the class IFModule
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Ashish Saboo
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

IFIDBuffer IFModule::execute() {
    IFIDBuffer buf;
    if(!go) {
        buf.invalid = true;
        ready = true;
        return buf;
    }
    int v = pc.read();
    int instruction = I$.request(v);
    pc.increment();
    buf.set(pc.val, instruction);
    buf.invalid = false;
    ready = true;
    return buf;
}
