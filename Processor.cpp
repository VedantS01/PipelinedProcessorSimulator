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
using namespace std;

void Processor::setup(ifstream &finI, ifstream &finD, ifstream &finR) {
    //read icache values
    for(int i = 0; i < NUMSETS; i++) {
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
    for(int i = 0; i < NUMSETS; i++) {
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
    int8 v;
    for(int i = 1; i < 16; i++) {
        finR >> hex >> v;
        //rf.write(i,v);
        rf.R[i].val = v;
    }

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

void Processor::startup() {
    pc.val = 0;
    HALT_SIGNAL = false;
    COMPLETE = false;
    clock_cycle = 0;
    while (!COMPLETE) {
        cycle();
    }
    
}

void Processor::cycle() {
    //processor clock cycle
    clock_cycle++;
    IFID = IF.execute();
    IDEX = IDRF.execute();
    EM = EX.execute();
    MW = MEM.execute();
    WB.execute();
}