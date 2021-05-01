/**
 *  Processor.cpp   :       Implements the class Processor
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Ashish Saboo, CS19B074
 * 
 * 
 **/

#include "Processor.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

//global variables for the processor
int total_instructions;
int arithmetic_instructions;
int logical_instructions;
int data_instructions;
int control_instructions;
int halt_instructions;
float cpi;
int total_stalls;
int data_stalls;
int control_stalls;

int RENAME;

void Processor::setup(ifstream &finI, ifstream &finD, ifstream &finR)
{
    //read icache values
    for (int i = 0; i < NUMSETS; i++)
    {
        finI >> hex >> I$.data[i].offset[0];
        finI >> hex >> I$.data[i].offset[1];
        finI >> hex >> I$.data[i].offset[2];
        finI >> hex >> I$.data[i].offset[3];
    }

    //read dcache values
    for (int i = 0; i < NUMSETS; i++)
    {
        finD >> hex >> D$.data[i].offset[0];
        finD >> hex >> D$.data[i].offset[1];
        finD >> hex >> D$.data[i].offset[2];
        finD >> hex >> D$.data[i].offset[3];
    }

    //read register file values
    int v;
    for (int i = 0; i < 16; i++)
    {
        finR >> hex >> v;
        //rf.write(i,v);
        rf.R[i].val = v;
    }

    //setup global counts
    total_instructions = 0;
    arithmetic_instructions = 0;
    logical_instructions = 0;
    data_instructions = 0;
    control_instructions = 0;
    halt_instructions = 0;
    total_stalls = 0;
    data_stalls = 0;
    control_stalls = 0;

    RENAME = NUM_REGS;
}

void Processor::startup()
{
    pc.val = 0;
    HALT_SIGNAL = false;
    COMPLETE = false;
    FLUSH = false;
    clock_cycle = 0;
    IF.go = true;
    wbstatus.invalid = true;
    wbstatus.ready = true;
    while (!COMPLETE)
    {
        cycle();
    }

    output();
}

void Processor::cycle()
{
    // processor clock cycle
    clock_cycle++;

    if (!WB.stall)
    {
        wbstatus = WB.execute();
    }
    if (IF.go)
    {
        IFID = IF.execute();
    }
    if (!EX.stall)
    {
        EM = EX.execute();
    }
    if (!IDRF.stall)
    {
        IDEX = IDRF.execute();
    }
    if (!MEM.stall)
    {
        MW = MEM.execute();
    }
    rf.reset();

    if (FLUSH)
    {
        //render last 2 computations useless
        IF.go = true;
        IDRF.ready = true;
        IDRF.stall = false;
        IFID.invalid = true;
        IDEX.invalid = true;
        FLUSH = false;
    }
    //forward
    if (WB.ready)
    {
        WB.mwBuf = MW;
        IF.go = true;
        IF.stall = false;
        IDRF.stall = false;
        EX.stall = false;
        MEM.stall = false;
        if (MEM.ready)
        {
            MEM.emBuf = EM;
            IF.go = true;
            IF.stall = false;
            IDRF.stall = false;
            EX.stall = false;
            if (EX.ready)
            {
                EX.idexBuf = IDEX;
                IF.go = true;
                IF.stall = false;
                IDRF.stall = false;
                if (IDRF.ready)
                {
                    IDRF.ifidBuf = IFID;
                    IF.go = true;
                    IF.stall = false;
                    if (IF.ready)
                    {
                        IF.go = true;
                    }
                    else
                    {
                        IF.go = false;
                    }
                }
                else
                {
                    IF.go = false;
                    IF.stall = true;
                    //IDRF.ifidBuf.ready = false;
                }
            }
            else
            {
                IF.go = false;
                IF.stall = true;
                IDRF.stall = true;
                //EX.idexBuf.ready = false;
            }
        }
        else
        {
            IF.go = false;
            IF.stall = true;
            IDRF.stall = true;
            EX.stall = true;
            // MEM.emBuf.ready = false;
            // IDRF.ifidBuf.ready = false;
        }
    }
    else
    {
        IF.go = false;
        IF.stall = true;
        IDRF.stall = true;
        EX.stall = true;
        MEM.stall = true;
        // IDRF.ifidBuf.ready = false;
        // WB.mwBuf.ready = false;
        COMPLETE = true; //?
    }
}

void Processor::output()
{
    ofstream fout;

    //rf
    fout.open("RF.out.txt");
    for (int i = 0; i < NUM_REGS; i++)
    {
        fout << hex << rf.R[i].read() << endl;
    }
    fout.close();

    //D$
    fout.open("D$.out.txt");
    for (int i = 0; i < NUMSETS; i++)
    {
        fout << std::hex << std::setw(2) << std::setfill('0') << D$.data[i].offset[0] << endl;
        fout << std::hex << std::setw(2) << std::setfill('0') << D$.data[i].offset[1] << endl;
        fout << std::hex << std::setw(2) << std::setfill('0') << D$.data[i].offset[2] << endl;
        fout << std::hex << std::setw(2) << std::setfill('0') << D$.data[i].offset[3] << endl;
    }
    fout.close();

    //processing data
    cpi = (float)clock_cycle / total_instructions;
    fout.open("Output.txt");
    fout << "Total number of instructions executed: " << std::dec << total_instructions << endl;
    fout << "Number of instrcutions in each class" << endl;
    fout << "Arithmetic instructions              : " << std::dec << arithmetic_instructions << endl;
    fout << "Logical instructions                 : " << std::dec << logical_instructions << endl;
    fout << "Data instructions                    : " << std::dec << data_instructions << endl;
    fout << "Control instructions                 : " << std::dec << control_instructions << endl;
    fout << "Halt instructions                    : " << std::dec << halt_instructions << endl;
    fout << "Cycles Per Instrcution               : " << std::dec << cpi << endl;
    fout << "Total number of stalls               : " << std::dec << total_stalls << endl;
    fout << "Data stalls (raw)                    : " << std::dec << data_stalls << endl;
    fout << "Control stalls                       : " << std::dec << control_stalls << endl;
    fout.close();
}