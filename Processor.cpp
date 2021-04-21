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

    //read dcache values
    for(int i = 0; i < NUMSETS; i++) {
        finD >> hex >> I$.data[i].offset[0];
        finD >> hex >> I$.data[i].offset[1];
        finD >> hex >> I$.data[i].offset[2];
        finD >> hex >> I$.data[i].offset[3];
    }

    //read register file values
    int8 v;
    for(int i = 1; i < 16; i++) {
        finR >> hex >> v;
        //rf.write(i,v);
        rf.R[i].val = v;
    }
}