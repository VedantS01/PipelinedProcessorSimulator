/**
 *  ALUModule.cpp   :       ALU
 *
 *  Version         :       1.0
 *  Author          :       Parth Ajmera
 *
 *  NOTE            :       IN DEVELOPEMENT STAGE
 *
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

EMBuffer EXModule::execute()
{
    EMBuffer buf;
    buf.invalid = true;
    buf.ready = true;
    if(idexBuf.invalid) {
        return buf;
    }
    int subop = idexBuf.subop;
    if(idexBuf.arithmetic)   //mode=0
    {
        buf.writeToRegister = true;
        if( (subop >> 1) & (subop & 1) ) //subop=3
        {
            //incrementer
            int val1 = idexBuf.srcval1;
            int val2 = inc.read();
            val1 = alu.adder(val1, val2, 0);
            buf.aluOutput = val1;
            buf.destval = val1;
            buf.validdest = true;
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            //multiplier
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            //TODO: sign extend and etc in case result is not coming right
            int val = alu.mul(val1, val2);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            //subtract
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            //TODO: sign extend and etc in case result is not coming right
            int val = alu.adder(val1, val2, 1);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
        else //subop=0
        {
            //add
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            //TODO: sign extend and etc in case result is not coming right
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
    }
    else if(idexBuf.logical)   //mode=1
    {
        buf.writeToRegister = true;
        if( (subop >> 1) & (subop & 1) ) //subop=3
        {
            //xor
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            int val = alu.XOR(val1, val2);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            //not
            int val1 = idexBuf.srcval1;
            int val = alu.NOT(val1);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            //or
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            int val = alu.OR(val1, val2);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
        else //subop=0
        {
            //and
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            int val = alu.AND(val1, val2);
            buf.aluOutput = val;
            buf.destval = val;
            buf.validdest = true;
        }
    }
    else if(idexBuf.load)
        {
            buf.writeToRegister = false;
            //calc effective address
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.offset;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
        }
    else if(idexBuf.store)
        {
            buf.writeToRegister = false;
            //calc effective address
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.offset;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
        }
    else if(idexBuf.jump)
        {
            buf.writeToRegister = false;
            //calc effective address
            int val1 = idexBuf.npc;
            int val2 = idexBuf.jump_addr;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;

            //set pc new value
        }
    else if(idexBuf.bneq)
        {
            buf.writeToRegister = false;
            //compare with 0
            int val1 = idexBuf.destval;
            int val2 = 0;
            if(val1 ^ val2) {
                //calc effective address
                int val1 = idexBuf.npc;
                int val2 = idexBuf.jump_addr;
                int val = alu.adder(val1, val2, 0);
                buf.aluOutput = val;
                
                //set pc new value
            }

            //keep same pc value;

        }
    buf.invalid = false;
    buf.ready = true;
    return buf;
}
