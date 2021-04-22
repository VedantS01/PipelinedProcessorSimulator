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
    int v = pc.read();
    //int v = pc.val;
    //cout << "in if module, addr is " << pc.val << endl; 
    int instruction = I$.request(v);
    npc.write(v);
    npc.increment();
    IFIDBuffer buf;
    buf.set(npc.val, instruction);
    return buf;
}
