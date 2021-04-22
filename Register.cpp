/**
 *  ICache.cpp      :       Implements the class Register
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

int8 Register::read()
{
    return val;
}

void Register::write(int8 _val)
{
    val = _val;
}

int16 Register16::read()
{
    return val;
}

void Register16::write(int16 _val)
{
    val = _val;
}

int8 RegisterFile::read(int rPos)
{
    if (fread1 == true && fread2 == true)
    {
        request_failed = true;
    }
    else if (fread1 == false)
    {
        fread1 = true;
        R[rPos].read();
    }
    else if (fread2 == false)
    {
        fread2 = true;
        R[rPos].read();
    }
}

void RegisterFile::write(int rPos, int8 _val)
{
    if (fwrite == true)
    {
        request_failed = true;
    }
    else
    {
        fwrite = true;
        R[rPos].write(_val);
    }
}