/**
 *  IFIDBuffer.cpp  :       Implements the buffer between EX,MW
 *
 *  Version         :       1.0
 *  Author          :       Parth Ajmera
 *
 *  NOTE            :       IN DEVELOPEMENT STAGE
 *
 **/

#include "Processor.h"
#include <iostream>
using namespace std;


EMBuffer::EMBuffer()
{
    invalid = true;

    HALT_SIGNAL = false;

    aluOutput = 0;
    npc = -1;
    load = false;
    store = false;
    writeToRegister = false;

    //will denote write_to register in arithmetic and logic operations and load instruction
    dest;
    //in case of store instruction or bneq instruction, dest is the concerned register and destval is its value;
    destval;
    validdest = false; //will be used in operator forwarding
}
