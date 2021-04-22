/**
 *  IDRFModule.cpp  :       Implements the class IFModule
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Saboo
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

IDEXBuffer IDRFModule::execute() {
    //decode here
    int instruction = ifidBuf.getInstruction();
    int opcode = instruction >> 12;
    int mode = opcode >> 2;
    int subop = opcode & 3;
    IDEXBuffer buf;
    if(mode == 0) {
        //buf.athmetic = 1;
        //buf.subop = subop;
        //fetch r
    } else if(mode == 1) {
        //buf.logical = 1;
        //buf.subop = subop;
        //fetch r
    } else if(mode == 2) {
        if(subop == 0) {
            //fetch r, m addr
            //buf.writer = true
        } else if(subop == 1) {
            //fetch r, m addr
            //buf.writem = true
        } else if(subop == 2) {
            //fetch m addr
            //buf.jump = 1
        } else {
            //fetch r, m addr
            //buf.jump = 2
        }
    } else if(mode == 3) {
        //issue halt signal
    }
}
