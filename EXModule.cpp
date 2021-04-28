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
    if(idexBuf.invalid) {
        ready = true;
        buf.invalid = true;
        return buf;
    }

    cout << "EX: " << idexBuf.npc << endl;
    buf.npc = idexBuf.npc;
    int subop = idexBuf.subop;
    if(idexBuf.arithmetic)   //mode=0
    {
        int val1, val2, val;
        if( (subop >> 1) & (subop & 1) ) //subop=3
        {
            //incrementer
            val1 = idexBuf.destval;
            val2 = inc.read();
            val = alu.adder(val1, val2, 0);
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            //multiplier
            val1 = idexBuf.srcval1;
            val2 = idexBuf.srcval2;
            //TODO: sign extend and etc in case result is not coming right
            val = alu.mul(val1, val2);
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            //subtract
            val1 = idexBuf.srcval1;
            val2 = idexBuf.srcval2;
            //TODO: sign extend and etc in case result is not coming right
            val = alu.adder(val1, val2, 1);
        }
        else //subop=0
        {
            //add
            val1 = idexBuf.srcval1;
            val2 = idexBuf.srcval2;
            //TODO: sign extend and etc in case result is not coming right
            val = alu.adder(val1, val2, 0);
        }
        buf.writeToRegister = true;
        buf.dest = idexBuf.dest;
        buf.aluOutput = val;
        buf.destval = val;
        buf.validdest = true;
    }
    else if(idexBuf.logical)   //mode=1
    {
        int val1, val2, val;
        if( (subop >> 1) & (subop & 1) ) //subop=3
        {
            //xor
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            int val = alu.XOR(val1, val2);
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            //not
            int val1 = idexBuf.srcval1;
            int val = alu.NOT(val1);
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            //or
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            int val = alu.OR(val1, val2);
        }
        else //subop=0
        {
            //and
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.srcval2;
            int val = alu.AND(val1, val2);
        }
        buf.writeToRegister = true;
        buf.dest = idexBuf.dest;
        buf.aluOutput = val;
        buf.destval = val;
        buf.validdest = true;
    }
    else if(idexBuf.load)
        {
            // buf.writeToRegister = false;
            buf.load = true;
            //calc effective address
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.offset;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
            buf.dest = idexBuf.dest;
            buf.validdest = idexBuf.validdest;
        }
    else if(idexBuf.store)
        {
            // buf.writeToRegister = false;
            buf.store = true;
            //calc effective address
            int val1 = idexBuf.srcval1;
            int val2 = idexBuf.offset;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
            buf.dest = idexBuf.dest;
            buf.destval = idexBuf.destval;
            buf.validdest = idexBuf.validdest;
        }
    else if(idexBuf.jump)
        {
            // buf.writeToRegister = false;
            //calc effective address
            int val1 = idexBuf.npc;
            int val2 = idexBuf.jump_addr;
                cout << "val1: " << val1 <<" val2:" << val2 ;
                val2 = val2 << 1;
                cout << "new : " << val2 << endl;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;

            //set pc new value
            pc.write(val);

            //generate go flush signal
            FLUSH = true;
            buf.invalid = true;
            ready = true;
            return buf;
        }
    else if(idexBuf.bneq)
        {
            // buf.writeToRegister = false;
            //compare with 0
            int val1 = idexBuf.destval;
            int val2 = 0;
            if(val1 == val2) {
                //calc effective address
                int val1 = idexBuf.npc;
                int val2 = idexBuf.jump_addr;
                cout << "val1: " << val1 <<" val2:" << val2 ;
                val2 = (val2 << 1) & 0xff;
                cout << "new : " << val2 << endl;
                int val = alu.adder(val1, val2, 0);
                buf.aluOutput = val;
                
                //set pc new value
                pc.write(val);

            }
            else
            {
                //keep same pc value;
                pc.write(idexBuf.npc);
            }

            //generate go flush signal
            FLUSH = true;
            buf.invalid = true;
            ready = true;
            return buf;
        }
    else if (idexBuf.HALT_SIGNAL)
        {
            buf.HALT_SIGNAL = true;
            buf.invalid = false;
            ready = false;
            return buf;
        }
    buf.invalid = false;
    ready = true;
    return buf;
}
