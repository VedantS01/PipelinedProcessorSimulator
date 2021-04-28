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
    void write(int _val); //_val is well inside 8 s
};

class Register16
{
public:
    int val;
    int read();
    void write(int _val); //_val is well inside 8 s
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
    flag request_failed;
    flag isWriting[16];
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
    //current instruction pc value
    int npcVal;

    //instruction fetched
    int instruction;

    //whether the contents of his buffer matter
    flag invalid;

    //redundant
    flag ready;

    //setter; redundant
    void set(int, int);

    //getter; redudant
    int getNPC();

    //getter; redundant
    int getInstruction();

    //constructor
    IFIDBuffer();
};

class IFModule
{
public: //in deveopement phase, let's keep everything public. We can introduce data hidinglater on.
    PC &pc;
    flag *stall;
    IFModule(PC &_pc, ICache &_I$, flag _stall[5]) : pc(_pc), I$(_I$)
    {
        stall = _stall;
        ready = true;
    }
    IFIDBuffer execute(/* args */);
    ICache &I$;
    PC npc;

    //a go signal to this module
    flag go;
    flag ready; //reduntant as of yet
};

class IDEXBuffer
{
public:
    //whether contents matter
    flag invalid;

    //redundant
    flag ready;

    //operation is arithmetic
    flag arithmetic;

    //operation in losgical
    flag logical;

    //operation is load
    flag load;

    //operation is store
    flag store;

    //operation is jump
    flag jump;

    //operation is bneq
    flag bneq;

    //issue halt signal to processor
    flag HALT_SIGNAL;

    //2bit subop for ALU
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

    //in load store, offset stores the immediate 4  value of address offset
    int offset;

    //stores jump offset in jump instructions
    int jump_addr;

    IDEXBuffer();
};

class IDRFModule
{
public:
    IDRFModule(RegisterFile &_rf, DCache &_D$, flag _stall[5]) : rf(_rf), D$(_D$), stall(_stall)
    {
        ready = true;
    }
    flag *stall;
    RegisterFile &rf;
    DCache &D$;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */);
    flag resolveBranch(int);
    
    //status flag
    flag ready;
};

/*
class EXModule
{
public:
    IDEXBuffer idexbuf;
    EMBuffer execute(IDEXBuffer);
    
};*/

class EMBuffer
{
public:
    flag invalid;
    flag ready;
    flag HALT_SIGNAL;

    int aluOutput;
    int npc;

    flag load;
    flag store;
    flag writeToRegister;

    //will denote write_to register in arithmetic and logic operations and load instruction
    int dest;
    //in case of store instruction or bneq instruction, dest is the concerned register and destval is its value;
    int destval;
    int validdest; //will be used in operator forwarding

    EMBuffer();
};

class ALU
{
    public:
    int adder(int , int, flag);
    int mul(int, int);
    int AND(int, int);
    int OR(int, int);
    int NOT(int);
    int XOR(int, int);
};

class EXModule
{
public:
    ALU &alu;
    PC &pc;
    flag &FLUSH;
    flag *stall;
    EXModule(ALU &_alu, flag _stall[5], PC &_pc, flag &f) : alu(_alu), stall(_stall), pc(_pc), FLUSH(f)
    {
        inc.write(1);
        ready = true;
    }
    IDEXBuffer idexBuf;
    Register inc;
    EMBuffer execute();
    
    //status flag(s)
    flag ready;
};

class MWBuffer
{
public:
    flag load;
    flag aluInstr;
    //issue halt signal to processor
    flag HALT_SIGNAL;

    int dest;
    int destval;
    flag validdest;

    int val;
    int lmd;

    int npc; 

    flag invalid;
    flag ready;
    MWBuffer();
};

class MEMModule
{
public:
    MEMModule(DCache &_D$, flag _stall[5]) : D$(_D$), stall(_stall)
    {
        ready = true;
    }
    flag *stall;

    DCache &D$;
    EMBuffer emBuf;
    Register LMD;
    MWBuffer execute(/* args */);

    //status flag(s)
    flag ready;
};

class WBSTATUS {
    public:
    flag invalid;
    flag ready;
    WBSTATUS() {
        invalid = true;
        ready = true;
    }
};

class WBModule
{
public:
    MWBuffer mwBuf;
    RegisterFile &rf;
    DCache &D$;
    WBModule(RegisterFile &_rf, DCache &_D$, flag _stall[5]) : rf(_rf), D$(_D$)
    {
        stall = _stall;
        ready = true;
    }
    flag *stall;

    //ICache &I$;
    WBSTATUS execute(/* args */);

    //status flag(s)
    flag ready;
};

class ControlUnit
{
};

class Processor
{
public:
    //ControlUnit CU;
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

    WBSTATUS wbstatus;

    ALU alu;
    flag HALT_SIGNAL;
    flag COMPLETE;
    flag FLUSH;
    int clock_cycle;

    flag stall[5];
    //more

    //more data

    //methods
    Processor() : IF(pc, I$, stall), IDRF(rf, D$, stall), EX(alu, stall, pc, FLUSH), MEM(D$, stall), WB(rf, D$, stall) {}
    void setup(ifstream &, ifstream &, ifstream &);
    void startup();
    void cycle();
    void output();

    //test individual elements
    void testicache();
};

#endif
