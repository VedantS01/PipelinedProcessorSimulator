/**
 *  IDRFModule.cpp  :       Implements the class IDEXBuffer
 * 
 *  Version         :       1.0
 *  Author          :       Sanchit Gupa
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

IDEXBuffer::IDEXBuffer()
{

    //whether contents matter
    invalid = true;

    //operation is arithmetic
    arithmetic = false;

    //operation in losgical
    logical = false;

    //operation is load
    load = false;

    //operation is store
    store = false;

    //operation is jump
    jump = false;

    //operation is bneq
    bneq = false;

    //issue halt signal to processor
    HALT_SIGNAL = false;

    //2bit subop for ALU
    subop = 0;

    //npc, denotes the address of the current instrcution
    npc = -1;

    //in case of arithmetic and logic instructions, this is first operand
    //in case of load store, this register is base
    src1;
    srcval1;
    validsrc1 = false; //will be used in operator forwarding

    //in case of arithmetic and logic instructions, this is second operand
    //in case of load store, src2 and srcval2 are not valid
    src2;
    srcval2;
    validsrc2 = false; //will be used in operator forwarding

    //will denote write_to register in arithmetic and logic operations and load instruction
    dest;
    //in case of store instruction or bneq instruction, dest is the concerned register and destval is its value;
    destval;
    validdest = false; //will be used in operator forwarding

    //in load store, offset stores the immediate 4  value of address offset
    offset = 0;

    //stores jump offset in jump instructions
    jump_addr = 2;
}