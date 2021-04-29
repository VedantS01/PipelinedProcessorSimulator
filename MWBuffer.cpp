/**
 *  MWModule.cpp    :       Implements the class MWBuffer
 * 
 *  Version         :       1.0
 *  Author          :       Sanchit Gupta
 * 
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

MWBuffer::MWBuffer()
{
    invalid = true;
    HALT_SIGNAL = false;

    load = false;
    aluInstr = false;

    validdest = false;

    npc = -1;
}