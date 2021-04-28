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

void IFIDBuffer::set(int npc, int instruction)
{
    npcVal = npc;
    this->instruction = instruction;
}

int IFIDBuffer::getNPC()
{
    return npcVal;
}

int IFIDBuffer::getInstruction()
{
    return instruction;
}

IFIDBuffer::IFIDBuffer()
{
    invalid = true;
    ready = true;

    npcVal = -1;
    instruction = 0xf000;
}