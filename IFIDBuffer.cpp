/**
 *  IFIDBuffer.cpp  :       Implements the class IFModule
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

void IFIDBuffer::set(int8 npc, int16 instruction) {
    npcVal = npc;
    this->instruction = instruction;
}

int8 IFIDBuffer::getNPC() {
    return npcVal;
}

int16 IFIDBuffer::getInstruction() {
    return instruction;
}