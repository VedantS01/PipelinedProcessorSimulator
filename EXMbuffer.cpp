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

void EXMBuffer::set(int target, int value) {
    memTarget = target;
    val = value;
}

int EXMBuffer::getTarget() {
    return memTarget;
}

int EXMBuffer::targetValue() {
    return value;
}
