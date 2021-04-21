/**
 *  Processor.h     :       H file for the simulator
 * 
 *  NOTE            :       DEVELOPEMENT STAGE
 **/

#include <iostream>
#include <cstdio>
#include <climits>
#include <conio.h>
#include <fstream>

#define int8 int8_t
#define NUM_REGS 16
#define flag bool

class Register {
    public:
    int8 val;
    int8 read();
    void write(int8 _val); //_val is well inside 8 bits
};

class RegisterFile {
    public:
    Register R[NUM_REGS];
    flag read1;
    flag read2;
    flag write;
    int8 read();
    void write(int rPos, int8 _val);
    RegisterFile();
};

class ICache {
    public:
};

class DCache {
    public:
};

class IFIDBuffer {

};

class IFModule {
    public:             //in deveopement phase, let's keep everything public. We can introduce data hidinglater on.
    Register pc;
    IFIDBuffer execute(/* args */);
    ICache I$;
};

class IDEXBuffer {

};

class IDRFModule {
    public:
    RegisterFile rf;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */);
};

class EMBuffer {

};

class ALU {

};

class EXModule {
    public:
    ALU alu;
    IDEXBuffer idexBuf;
    EMBuffer execute(/* args */);
};

class MWBuffer {
    
};

class MEMModule {
    public:
    DCache D$;
    EMBuffer emBuf;
    MWBuffer execute(/* args */);
};

class WBModule {
    public:
    MWBuffer mwBuf;
    void execute(/* args */);
};

class ControlUnit {

};

class Processor {
    public:
    ControlUnit CU;
    ICache I$;
    DCache D$;
    RegisterFile rf;
    //more data

    //methods
    void setup(ifstream &, ifstream &, ifstream &);
};