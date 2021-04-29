/**
 *  Register.cpp    :       Implements the class Register
 * 
 *  Version         :       1.0
 *  Author          :       Sanchit Gupta
 * 
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

int Register::read()
{
    return val;
}

void Register::write(int _val)
{
    val = _val;
}

int Register16::read()
{
    return val;
}

void Register16::write(int _val)
{
    val = _val;
}

int RegisterFile::read(int rPos)
{
    if (fread1 == true && fread2 == true)
    {
        request_failed = true;
    }
    else if (fread1 == false)
    {
        fread1 = true;
        return R[rPos].read();
    }
    else if (fread2 == false)
    {
        fread2 = true;
        return R[rPos].read();
    }
    return 0;
}

void RegisterFile::write(int rPos, int _val)
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

RegisterFile::RegisterFile()
{
    for (int i = 0; i < 16; i++)
    {
        isWriting[i] = 0;
    }
    request_failed = false;
    fread1 = fread2 = fwrite = false;
    busy = false;
}

void RegisterFile::reset()
{
    request_failed = false;
    fread1 = fread2 = fwrite = false;
}

void RegisterFile::getBusy()
{
    busy = true;
}

void RegisterFile::relax()
{
    busy = false;
}