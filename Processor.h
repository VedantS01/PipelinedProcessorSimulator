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
    bool isWriting[16];
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
    bool *stall;
    IFModule(PC &_pc, ICache &_I$, bool _stall[5]) : pc(_pc), I$(_I$)
    {
        stall = _stall;
    }
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
    flag bneq;
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
    IDRFModule(RegisterFile &_rf, DCache &_D$, bool _stall[5]) : rf(_rf), D$(_D$), stall(_stall)
    {
    }
    bool *stall;
    RegisterFile &rf;
    DCache &D$;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */) {}
    bool resolveBranch(int);
};

class EXModule
{
public:
    IDEXBuffer idexbuf;
    EMBuffer execute(IDEXBuffer);
    
};

class EMBuffer
{
public:
    flag invalid;
    flag HALT_SIGNAL;

    int aluOutput;
    flag load;
    flag store;
    flag writeToRegister;

    //will denote write_to register in arithmetic and logic operations and load instruction
    int dest;
    //in case of store instruction or bneq instruction, dest is the concerned register and destval is its value;
    int destval;
    int validdest; //will be used in operator forwarding
};

class ALU
{
    public:
    int adder(int , int, bool);
    int mul(int, int);
    int and(int, int);
    int or(int, int);
    int not(int);
    int xor(int, int);
};

class EXModule
{
public:
    ALU &alu;
    bool *stall;
    EXModule(ALU &_alu, bool _stall[5]) : alu(_alu), stall(_stall)
    {
        inc.write(1);
    }
    IDEXBuffer idexBuf;
    Register inc;
    EMBuffer execute(/* args */) {}
};

class MWBuffer
{
public:
    bool load;
    bool aluInstr;
    int dest;
    int val;
    int lmd;
    bool invalid;
};

class MEMModule
{
public:
    MEMModule(DCache &_D$, bool _stall[5]) : D$(_D$), stall(_stall)
    {
        }
    bool *stall;

    DCache &D$;
    EMBuffer emBuf;
    Register LMD;
    MWBuffer execute(/* args */) {}
};

class WBModule
{
public:
    MWBuffer mwBuf;
    RegisterFile &rf;
    DCache &D$;
    WBModule(RegisterFile &_rf, DCache &_D$, bool _stall[5]) : rf(_rf), D$(_D$)
    {
        stall = _stall;
    }
    bool *stall;

    //ICache &I$;
    void execute(/* args */) {}
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

    ALU alu;
    flag HALT_SIGNAL;
    flag COMPLETE;
    int clock_cycle;

    bool stall[5];
    //more

    //more data

    //methods
    Processor() : IF(pc, I$, stall), IDRF(rf, D$, stall), EX(alu, stall), MEM(D$, stall), WB(rf, D$, stall) {}
    void setup(ifstream &, ifstream &, ifstream &);
    void startup();
    void cycle();

    //test individual elements
    void testicache();
};

#endif
