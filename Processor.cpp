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

    /*
    //set up modules
    //IF Module initialisations
    IF.I$ = I$;
    IF.pc = pc;
    
    //IDRFModule initialisations
    IDRF.rf = rf;

    //EX Module initialisations
    EX.alu = alu;

    //MEM Module initialisations
    MEM.D$ = D$;

    //WB Module initialisations
    WB.D$ = D$;
    //WB.I$ = I$;
    WB.rf = rf;
    */
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
    clock_cycle = 0;
    IF.go = true;
    wbstatus.invalid = true;
    wbstatus.ready = true;
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
    cycle();
}

void Processor::cycle()
{
    // processor clock cycle
    streambuf *orig_buf = cout.rdbuf();

    // set null
    cout.rdbuf(NULL);
    clock_cycle++;
    // int stages_active = 0;
    /* WILL WORK ON THIS ONE
    if (!stall[0])
    {
        IFID = IF.execute();
        // stages_active++;
    }
    if (!stall[1])
    {
        IDEX = IDRF.execute();
    }

    HALT_SIGNAL = IDEX.HALT_SIGNAL;

    if (!stall[2])
    {
        EM = EX.execute();
    }
    if (!stall[3])
    {
        MW = MEM.execute();
    }
    if (!stall[4])
    {
        WB.execute();
    }

    IDRF.ifidBuf = IFID;
    EX.idexBuf = IDEX;
    MEM.emBuf = EM;
    WB.mwBuf = MW;

    */
    //cout << "1:\n";

    int flag1 = 0;

    cout << "IF.GO" << IF.go << endl;
    if (IF.go)
    {
        IFID = IF.execute();
    }
    if (!IDRF.ifidBuf.invalid)
    {
        cout << "counting" << endl;
        IDEX = IDRF.execute();
    }
    else
    {
        flag1 = 1;
        cout << "Yeahhhhhh";
        IDRF.ifidBuf.invalid = false;
        if (IDRF.ifidBuf.ready)
        {
            cout << "Ready";
            IF.go = true;
        }
    }
    if (!EX.idexBuf.invalid)
    {
        EM = EX.execute();
    }
    else
    {
        flag1 = 2;
        cout << "Yeahhhhhh";
        EX.idexBuf.invalid = false;
        if (EX.idexBuf.ready)
        {
            cout << "Ready";
            IF.go = true;
        }
    }
    if (!MEM.emBuf.invalid)
    {
        MW = MEM.execute();
    }
    else
    {
        flag1 = 3;
        cout << "Yeahhhhhh";
        MEM.emBuf.invalid = false;
        if (MEM.emBuf.ready)
        {
            cout << "Ready";
            IF.go = true;
        }
    }
    if (!WB.mwBuf.invalid)
    {
        wbstatus = WB.execute();
    }
    else
    {
        flag1 = 4;
        cout << "Yeahhhhhh";
        WB.mwBuf.invalid = false;
        if (WB.mwBuf.ready)
        {
            cout << "Ready";
            IF.go = true;
        }
    }

    //forward
    if (wbstatus.ready)
    {
        WB.mwBuf = MW;
        if (MW.ready)
        {
            MEM.emBuf = EM;
            if (EM.ready)
            {
                EX.idexBuf = IDEX;
                //cout << "2:\n";
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
            IDRF.ifidBuf.invalid = true;
        }
    }
    else
    {
        cout << "Blocking-2" << endl;
        IF.go = false;
        IDRF.ifidBuf.invalid = true;
        EX.idexBuf.invalid = true;
    }
}
else
{
    cout << "Blocking-1" << endl;
    IF.go = false;
    IDRF.ifidBuf.invalid = true;
    EX.idexBuf.invalid = true;
    MEM.emBuf.invalid = true;
    // IDRF.ifidBuf.invalid = true;
}
}
else
{
    cout << "Blocking" << endl;
    IF.go = false;
    IDRF.ifidBuf.invalid = true;
    EX.idexBuf.invalid = true;
    MEM.emBuf.invalid = true;
    // IDRF.ifidBuf.invalid = true;
    WB.mwBuf.invalid = true;
}

if (flag1 == 0)
{
}
else if (flag1 == 1)
{
    cout << "Yeahhhhhh";
    IDRF.ifidBuf.invalid = false;
    if (IDRF.ifidBuf.ready)
    {
        cout << "Ready";
        IF.go = true;
    }
}
else if (flag1 == 2)
{
    cout << "Yeahhhhhh";
    EX.idexBuf.invalid = false;
    if (EX.idexBuf.ready)
    {
        cout << "Ready";
        IF.go = true;
    }
}
else if (flag1 == 3)
{
    cout << "Yeahhhhhh";
    MEM.emBuf.invalid = false;
    if (MEM.emBuf.ready)
    {
        cout << "Ready";
        IF.go = true;
    }
}

cout << IDRF.ifidBuf.invalid << "Informative" << endl;

if (clock_cycle == 10)
{
    HALT_SIGNAL = true;
    COMPLETE = true;
}
//pc.increment();
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

/*
Processor::Processor() {
    //set up modules
    //IF Module initialisations
    IF.I$ = I$;
    IF.pc = pc;
    
    //IDRFModule initialisations
    IDRF.rf = rf;

    //EX Module initialisations
    EX.alu = alu;

    //MEM Module initialisations
    MEM.D$ = D$;

    //WB Module initialisations
    WB.D$ = D$;
    //WB.I$ = I$;
    WB.rf = rf;
}
*/