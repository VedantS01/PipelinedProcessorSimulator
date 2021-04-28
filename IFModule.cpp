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
    cout << "IF:" << v << endl;
    //int v = pc.val;
    //cout << "in if module, addr is " << pc.val << endl; 
    int instruction = I$.request(v);
    //npc.write(v);
    //npc.increment();
    pc.increment();
    buf.set(v, instruction);
    buf.invalid = false;
    buf.ready = true;
    ready = true;
    return buf;
}
