/**
 *  IFIDBuffer.cpp  :       Implements the class IFIDBuffer
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Ashish Saboo
 * 
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

    npcVal = -1;
    instruction = 0xf000;
}