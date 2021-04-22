/**
 *  Processor.h     :       H file for the simulator
 * 
 *  NOTE            :       DEVELOPEMENT STAGE
 **/

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <cstdio>
#include <climits>
#include <fstream>
using namespace std;

#define int8 int8_t
#define int16 int16_t
#define NUM_REGS 16
#define flag bool

#define IWIDTH 16
#define DWIDTH 8
#define NUMSETS 64
#define BLOCK_SIZE 4

class Register
{
public:
    int8 val;
    int8 read();
    void write(int8 _val); //_val is well inside 8 bits
};

class Register16
{
public:
    int16 val;
    int16 read();
    void write(int16 _val); //_val is well inside 8 bits
};

class PC
{
public:
    int8 val;
    int8 read();
    void write(int8 _val);
    void increment();
};

class RegisterFile
{
public:
    bool request_failed;
    Register R[NUM_REGS];
    flag fread1;
    flag fread2;
    flag fwrite;
    int8 read(int rPos);
    void write(int rPos, int8 _val);
    RegisterFile()
    {
        request_failed = false;
        fread1 = fread2 = fwrite = false;
    }
};

class Block
{
public:
    int8 offset[BLOCK_SIZE];
};

class ICache
{
public:
    Block data[NUMSETS];
    int16 request(int8);
};

class DCache
{
public:
    Block data[NUMSETS];
    int8 request(int8);
    void write(int8, int8);
};

class IFIDBuffer
{
public:
    int8 npcVal;
    int16 instruction;
    void set(int8, int16);
    int8 getNPC();
    int16 getInstruction();
};

class IFModule
{
public: //in deveopement phase, let's keep everything public. We can introduce data hidinglater on.
    PC &pc;
    IFIDBuffer execute(/* args */);
    ICache &I$;
    PC npc;
};

class IDEXBuffer
{
};

class IDRFModule
{
public:
    RegisterFile &rf;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */);
};

class EMBuffer
{
};

class ALU
{
};

class EXModule
{
public:
    ALU &alu;
    IDEXBuffer idexBuf;
    EMBuffer execute(/* args */);
};

class MWBuffer
{
};

class MEMModule
{
public:
    DCache &D$;
    EMBuffer emBuf;
    MWBuffer execute(/* args */);
};

class WBModule
{
public:
    MWBuffer mwBuf;
    RegisterFile &rf;
    DCache &D$;
    //ICache &I$;
    void execute(/* args */);
};

class ControlUnit
{
};

class Processor
{
public:
    ControlUnit CU;
    ICache I$;
    DCache D$;
    RegisterFile rf;
    PC pc;
    Register16 IR;
    IFModule IF;
    IFIDBuffer IFID;
    IDRFModule IDRF;
    IDEXBuffer IDEX;
    EXModule EX;
    EMBuffer EM;
    MEMModule MEM;
    MWBuffer MW;
    WBModule WB;
    ALU alu;
    flag HALT_SIGNAL;
    flag COMPLETE;
    int clock_cycle;

    //more data

    //methods
    void setup(ifstream &, ifstream &, ifstream &);
    void startup();
    void cycle();
};

#endif