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
    int8 v = pc.read();
    int16 instruction = I$.request(v);
    //npc.increment();
    npc.val = v + 2;
    if(npc.val >= 256) {
        npc.val = npc.val - 256;
    }
    IFIDBuffer buf;
    buf.set(npc.val, instruction);
}