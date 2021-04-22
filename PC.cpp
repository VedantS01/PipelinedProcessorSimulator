/**
 *  PC.cpp          :       Implements the class PC
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

int PC::read()
{
    return val;
}

void PC::write(int _val)
{
    val = _val;
}

void PC::increment() {
    val += 2;
}