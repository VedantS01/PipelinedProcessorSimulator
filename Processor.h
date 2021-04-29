/**
 *  Processor.h     :       H file for the simulator
 * 
 *  Version         :       1.0
 * 
 *  Author(s)       :       Vedant Saboo (CS19B074), Sanchit Gupta(CS19B071), Parth Ajmera (CS19B065)
 * 
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

//NOTE: set this to enable operand forwarding, reset to disable
#define ENABLE_OPEARND_FORWARDING true

//global variables for the processor
extern int total_instructions;
extern int arithmetic_instructions;
extern int logical_instructions;
extern int data_instructions;
extern int control_instructions;
extern int halt_instructions;
extern float cpi;
extern int total_stalls;
extern int data_stalls;
extern int control_stalls;

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
    int isWriting[NUM_REGS];
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
    void write(int, int);
};

class DCache
{
public:
    DBlock data[NUMSETS];
    int request(int);
    void write(int, int);
};

class ForwardingUnit;

class IFIDBuffer
{
public:
    //current instruction pc value
    int npcVal;

    //instruction fetched
    int instruction;

    //whether the contents of his buffer matter
    flag invalid;

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
    IFModule(PC &_pc, ICache &_I$) : pc(_pc), I$(_I$)
    {
        stall = false;
        ready = true;
    }
    IFIDBuffer execute(/* args */);
    ICache &I$;
    PC npc;

    //a go signal to this module
    flag go;
    flag ready; //redundant as of yet
    flag stall;
};

class IDEXBuffer
{
public:
    //whether contents matter
    flag invalid;

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
    IDRFModule(RegisterFile &_rf, DCache &_D$, ForwardingUnit &_FU) : rf(_rf), D$(_D$), FU(_FU)
    {
        stall = false;
        ready = true;
    }
    RegisterFile &rf;
    DCache &D$;
    ForwardingUnit &FU;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */);
    flag resolveBranch(int);
    
    //status flag
    flag ready;
    flag stall;
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
    EXModule(ALU &_alu, PC &_pc, flag &f) : alu(_alu), pc(_pc), FLUSH(f)
    {
        inc.write(1);
        ready = true;
        stall = false;
    }
    IDEXBuffer idexBuf;
    Register inc;
    EMBuffer execute();
    
    //status flag(s)
    flag ready;
    flag stall;
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
    MWBuffer();
};

class MEMModule
{
public:
    MEMModule(DCache &_D$) : D$(_D$)
    {
        stall = false;
        ready = true;
    }

    DCache &D$;
    EMBuffer emBuf;
    Register LMD;
    MWBuffer execute(/* args */);

    //status flag(s)
    flag ready;
    flag stall;
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
    WBModule(RegisterFile &_rf, DCache &_D$) : rf(_rf), D$(_D$)
    {
        stall = false;
        ready = true;
    }

    //ICache &I$;
    WBSTATUS execute(/* args */);

    //status flag(s)
    flag ready;
    flag stall;
};

//register forwarding unit
/**
 * REGISTER FOWARDING UNIT
 * VERSION 1.0
 * AUTHOR : VEDANT SABOO, CS19B074
 **/
class ForwardingUnit
{
    public:
    IFIDBuffer &IFID;
    IDEXBuffer &IDEX;
    EMBuffer &EM;
    MWBuffer &MW;

    flag request_success;
    int request(int);
    void renderInvalidIfValid(int);
    ForwardingUnit(IFIDBuffer &ifid, IDEXBuffer& idex, EMBuffer &em, MWBuffer &mw) : IFID(ifid), IDEX(idex), EM(em), MW(mw)
    {
        request_success = false;
    }
};
/**
 * END
 **/

class Processor
{
public:
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

    //register forwarding unit
    ForwardingUnit FU;

    //methods
    Processor() : IF(pc, I$),FU(IFID, IDEX, EM, MW), IDRF(rf, D$, FU), EX(alu, pc, FLUSH), MEM(D$), WB(rf, D$) {}
    void setup(ifstream &, ifstream &, ifstream &);
    void startup();
    void cycle();
    void output();
};

#endif
