/**
 *  Processor.cpp   :       Implements the class Processor
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Ashish Saboo
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
 * 
 **/

#include "Processor.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

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

    //ofstream fout;
    /*
    fout.open("debugi.txt");
    for(int i = 0; i < NUMSETS; i++) {
        fout << hex << I$.data[i].offset[0] << endl;
        fout << hex << I$.data[i].offset[1] << endl;
        fout << hex << I$.data[i].offset[2] << endl;
        fout << hex << I$.data[i].offset[3] << endl;
    }
    fout.close();
    */

    //read dcache values
    for (int i = 0; i < NUMSETS; i++)
    {
        finD >> hex >> D$.data[i].offset[0];
        finD >> hex >> D$.data[i].offset[1];
        finD >> hex >> D$.data[i].offset[2];
        finD >> hex >> D$.data[i].offset[3];
    }

    /*
    fout.open("debugd.txt");
    for(int i = 0; i < NUMSETS; i++) {
        fout << hex << D$.data[i].offset[0] << endl;
        fout << hex << D$.data[i].offset[1] << endl;
        fout << hex << D$.data[i].offset[2] << endl;
        fout << hex << D$.data[i].offset[3] << endl;
    }
    fout.close();
    */

    //read register file values
    int v;
    for (int i = 0; i < 16; i++)
    {
        finR >> hex >> v;
        //rf.write(i,v);
        rf.R[i].val = v;
    }

}

void Processor::startup()
{
    for (int i = 0; i < 5; i++)
    {
        stall[i] = false;
    }
    pc.val = 0;
    HALT_SIGNAL = false;
    COMPLETE = false;
    FLUSH = false;
    clock_cycle = 0;
    IF.go = true;
    wbstatus.invalid = true;
    wbstatus.ready = true;
    while (! COMPLETE)
    {
        cycle();
    }

    output();
    
}

void Processor::cycle()
{
    // processor clock cycle
    streambuf *orig_buf = cout.rdbuf();

    // set null
    clock_cycle++;

    int flag1 = 0;

    if (IF.go)
    {
        IFID = IF.execute();
    }
    if (!IDRF.ifidBuf.invalid)
    {
        IDEX = IDRF.execute();
    }
    if (!EX.idexBuf.invalid)
    {
        EM = EX.execute();
    }
    if (!MEM.emBuf.invalid)
    {
        MW = MEM.execute();
    }
    if (!WB.mwBuf.invalid)
    {
        wbstatus = WB.execute();
    }
    rf.reset();

    //forward
    if (WB.ready)
    {
        WB.mwBuf = MW;
        if (MEM.ready)
        {
            MEM.emBuf = EM;
            if (EX.ready)
            {
                EX.idexBuf = IDEX;
                if (IDRF.ready)
                {
                    IDRF.ifidBuf = IFID;
                    if (IF.ready) 
                    {
                        IF.go = true;
                    }
                    else
                    {
                        cout << "Blocking-4" << endl;
                        IF.go = false;
                    }
                }
                else
                {
                    cout << "Blocking-3" << endl;
                    IF.go = false;
                    IDRF.ifidBuf.ready = false;
                }
            }
            else
            {
                cout << "Blocking-2" << endl;
                IF.go = false;
                IDRF.ifidBuf.ready = false;
                EX.idexBuf.ready = false;
            }
        }
        else
        {
            cout << "Blocking-1" << endl;
            IF.go = false;
            IDRF.ifidBuf.ready = false;
            EX.idexBuf.ready = false;
            MEM.emBuf.ready = false;
            // IDRF.ifidBuf.ready = false;
        }
    }
    else
    {
        cout << "Blocking" << endl;
        IF.go = false;
        IDRF.ifidBuf.ready = false;
        EX.idexBuf.ready = false;
        MEM.emBuf.ready = false;
        // IDRF.ifidBuf.ready = false;
        WB.mwBuf.ready = false;
        COMPLETE = true;
    }
    if(FLUSH) {
        IF.go = true;
        IDRF.ready = true;
        //IFID.invalid = true;
        FLUSH = false;
    }
}

void Processor::testicache()
{
    ofstream fout;
    fout.open("debugif.txt");
    for (int i = 0; i < NUMSETS; i++)
    {
        fout << hex << I$.data[i].offset[0] << endl;
        fout << hex << I$.data[i].offset[1] << endl;
        fout << hex << I$.data[i].offset[2] << endl;
        fout << hex << I$.data[i].offset[3] << endl;
    }
    fout.close();
}

void Processor::output() {
    ofstream fout;
    
    //rf
    fout.open("RF.out.txt");
    for(int i = 0; i < NUM_REGS; i++) {
        fout << hex << rf.R[i].read() << endl;
    }
    fout.close();

    //D$
    fout.open("D$.out.txt");
    for(int i = 0; i < NUMSETS; i++) {
        fout << hex << D$.data[i].offset[0] << endl;
        fout << hex << D$.data[i].offset[1] << endl;
        fout << hex << D$.data[i].offset[2] << endl;
        fout << hex << D$.data[i].offset[3] << endl;
    }
    fout.close();
}