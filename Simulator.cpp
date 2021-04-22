#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <fstream>
using namespace std;

#define IFILE "ICacheData.txt"
#define DFILE "DCacheData.txt"
#define RFILE "RegisterData.txt"

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