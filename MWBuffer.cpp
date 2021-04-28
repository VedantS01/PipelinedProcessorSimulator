/**
 *  IDRFModule.cpp  :       Implements the class MWBuffer
 * 
 *  Version         :       1.0
 *  Author          :       Sanchit Gupta
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
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

    dest;
    destval;
    validdest = false;

    val;

    lmd;

    npc = -1;
}