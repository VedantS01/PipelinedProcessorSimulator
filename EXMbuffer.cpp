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

struct EXBuffer
{
    int memTarget;
    int val;
};
/*
class EXMBuffer
{
  struct EXBuffer buffercomp;
public:
  void set(int,int);
  int getTarget();
  int targetValue();
};

void EXMBuffer::set(int target, int value) {
    buffercomp.memTarget = target;
    buffercomp.val = value;
}

int EXMBuffer::getTarget() {
    return buffercomp.memTarget;
}

int EXMBuffer::targetValue() {
    return buffercomp.value;
}
*/
