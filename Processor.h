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
#define uint8 uint8_t
#define int16 int16_t
#define uint16 uint16_t
#define NUM_REGS 16
#define flag bool

#define IWIDTH 16
#define DWIDTH 8
#define NUMSETS 64
#define BLOCK_SIZE 4

class Register
{
public:
    int val;
    int read();
    void write(int _val); //_val is well inside 8 bits
};

class Register16
{
public:
    int val;
    int read();
    void write(int _val); //_val is well inside 8 bits
};

class PC
{
public:
    int val;
    int read();
    void write(int _val);
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
    flag busy;
    int read(int rPos);
    void write(int rPos, int _val);
    void reset();
    void getBusy();
    void relax();
    RegisterFile();
};

class IBlock
{
public:
    int offset[BLOCK_SIZE];
};

class DBlock
{
public:
    int offset[BLOCK_SIZE];
};

class ICache
{
public:
    IBlock data[NUMSETS];
    int request(int);
};

class DCache
{
public:
    DBlock data[NUMSETS];
    int request(int);
    void write(int, int);
};

class IFIDBuffer
{
public:
    int npcVal;
    int instruction;
    flag invalid;
    void set(int, int);
    int getNPC();
    int getInstruction();
};

class IFModule
{
public: //in deveopement phase, let's keep everything public. We can introduce data hidinglater on.
    PC &pc;
    IFModule(PC& _pc, ICache & _I$) : pc(_pc),I$(_I$) {}
    IFIDBuffer execute(/* args */);
    ICache &I$;
    PC npc;
};

class IDEXBuffer
{
    public:
    flag invalid;
    flag arithmetic;
    flag logical;
    flag load;
    flag store;
    flag jump;
    flag HALT_SIGNAL;
    int subop;

    //npc, denotes the address of the current instrcution
    int npc;

    //in case of arithmetic and logic instructions, this is first operand
    //in case of load store, this register is base
    int src1;
    int srcval1;
    flag validsrc1; //will be used in operator forwarding

    //in case of arithmetic and logic instructions, this is second operand
    //in case of load store, src2 and srcval2 are not valid
    int src2;
    int srcval2; 
    flag validsrc2; //will be used in operator forwarding


    //will denote write_to register in arithmetic and logic operations and load instruction 
    int dest;
    //in case of store instruction or bneq instruction, dest is the concerned register and destval is its value;
    int destval;
    int validdest; //will be used in operator forwarding

    //in load store, offset stores the immediate 4 bit value of address offset
    int offset;
    
    //stores jump offset in jump instructions
    int jump_addr;
};

class IDRFModule
{
public:
    IDRFModule(RegisterFile& _rf, DCache& _D$) : rf(_rf), D$(_D$) {}
    RegisterFile &rf;
    DCache &D$;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */){}
    bool resolveBranch(int);
};

class EMBuffer
{
    public:
    int aluOutput;
    flag load;
    flag store;
    flag writeToRegister;
    int dest;
    int memTarget;
    int val;
    void set(int,int);
    int getTarget();
    int getValue();
};

class ALU
{
};

class EXModule
{
public:
    ALU &alu;
    EXModule(ALU& _alu) : alu(_alu) {}
    IDEXBuffer idexBuf;
    EMBuffer execute(/* args */){}
};

class MWBuffer
{
};

class MEMModule
{
public:
    MEMModule(DCache& _D$): D$(_D$){}
    DCache &D$;
    EMBuffer emBuf;
    Register LMD;
    MWBuffer execute(/* args */){}
};

class WBModule
{
public:
    MWBuffer mwBuf;
    RegisterFile &rf;
    DCache &D$;
    WBModule(RegisterFile& _rf, DCache& _D$): rf(_rf), D$(_D$){}
    //ICache &I$;
    void execute(/* args */){}
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
    Processor(): IF(pc, I$) , IDRF(rf, D$), EX(alu), MEM(D$), WB(rf, D$) {}
    void setup(ifstream &, ifstream &, ifstream &);
    void startup();
    void cycle();

    //test individual elements
    void testicache();
};

#endif
