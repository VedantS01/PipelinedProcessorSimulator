#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <fstream>
using namespace std;

#define IFILE "ICacheData.txt"
#define DFILE "DCacheData.txt"
#define RFILE "RegisterData.txt"

// //global variables for the processor
// extern int total_instructions;
// extern int arithmetic_instructions;
// extern int logical_instructions;
// extern int data_instructions;
// extern int control_instructions;
// extern int halt_instructions;
// extern float cpi;
// extern int total_stalls;
// extern int data_stalls;
// extern int control_stalls;

#include "Processor.h"

int main() {
    Processor processor;
    ifstream finI, finD, finR;
    finI.open(IFILE);
    finD.open(DFILE);
    finR.open(RFILE);
    processor.setup(finI, finD, finR);
    processor.startup();
    //processor.testicache();
}