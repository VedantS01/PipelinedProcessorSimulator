/**
 *  ExModule.cpp    :       Implements class EXModule
 *
 *  Version         :       1.0
 *  Author(s)       :       Vedant Saboo (CS19B074) & Parth Ajmera(CS19B065)
 *
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

    buf.npc = idexBuf.npc;
    int subop = idexBuf.subop;
    if(idexBuf.arithmetic)   //mode=0
    {
        int val1, val2, val;
        if( (subop >> 1) & (subop & 1) ) //subop=3
        {
            //incrementer
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            val2 = inc.read();
            val = alu.adder(val1, val2, 0);
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            //multiplier
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            if(!idexBuf.src2.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src2.tag);
                if(FU.request_success)
                {
                    val2 = tval;
                    idexBuf.src2.data = tval;
                    idexBuf.src2.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val2 = idexBuf.src2.data;
            //TODO: sign extend and etc in case result is not coming right
            val = alu.mul(val1, val2);
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            //subtract
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            if(!idexBuf.src2.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src2.tag);
                if(FU.request_success)
                {
                    val2 = tval;
                    idexBuf.src2.data = tval;
                    idexBuf.src2.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val2 = idexBuf.src2.data;

            val = alu.adder(val1, val2, 1);
        }
        else //subop=0
        {
            //add
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    cout << "count" << endl;
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            if(!idexBuf.src2.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src2.tag);
                if(FU.request_success)
                {
                    val2 = tval;
                    idexBuf.src2.data = tval;
                    idexBuf.src2.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val2 = idexBuf.src2.data;
            val = alu.adder(val1, val2, 0);
        }
        buf.writeToRegister = true;
        buf.dest = idexBuf.dest.tag;
        buf.aluOutput = val;
        buf.destval = val;
        buf.validdest = true;
        arithmetic_instructions++;
    }
    else if(idexBuf.logical)   //mode=1
    {
        int val1, val2, val;
        if( (subop >> 1) & (subop & 1) ) //subop=3
        {
            //xor
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            if(!idexBuf.src2.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src2.tag);
                if(FU.request_success)
                {
                    val2 = tval;
                    idexBuf.src2.data = tval;
                    idexBuf.src2.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val2 = idexBuf.src2.data;
            val = alu.XOR(val1, val2);
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            //not
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            val = alu.NOT(val1);
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            //or
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            if(!idexBuf.src2.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src2.tag);
                if(FU.request_success)
                {
                    val2 = tval;
                    idexBuf.src2.data = tval;
                    idexBuf.src2.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val2 = idexBuf.src2.data;
            val = alu.OR(val1, val2);
        }
        else //subop=0
        {
            //and
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            if(!idexBuf.src2.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src2.tag);
                if(FU.request_success)
                {
                    val2 = tval;
                    idexBuf.src2.data = tval;
                    idexBuf.src2.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val2 = idexBuf.src2.data;
            val = alu.AND(val1, val2);
        }
        buf.writeToRegister = true;
        buf.dest = idexBuf.dest.tag;
        buf.aluOutput = val;
        buf.destval = val;
        buf.validdest = true;
        logical_instructions++;
    }
    else if(idexBuf.load)
        {
            // buf.writeToRegister = false;
            buf.load = true;
            //calc effective address
            int val1;
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            int val2 = idexBuf.offset;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
            buf.dest = idexBuf.dest.tag;
            buf.validdest = idexBuf.dest.valid;
            data_instructions++;
        }
    else if(idexBuf.store)
        {
            // buf.writeToRegister = false;
            buf.store = true;
            //calc effective address
            int val1, val2, val;
            val2 = idexBuf.offset;
            if(!idexBuf.src1.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.src1.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.src1.data = tval;
                    idexBuf.src1.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.src1.data;
            val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;
            buf.dest = idexBuf.dest.tag;
            buf.destval = idexBuf.dest.data;
            buf.validdest = idexBuf.dest.valid;
            data_instructions++;
        }
    else if(idexBuf.jump)
        {
            control_instructions++;
            // buf.writeToRegister = false;
            //calc effective address
            int val1 = idexBuf.npc;
            int val2 = idexBuf.jump_addr;
            val2 = val2 << 1;
            int val = alu.adder(val1, val2, 0);
            buf.aluOutput = val;

            //set pc new value
            pc.write(val);

            //generate go flush signal
            total_instructions++;
            FLUSH = true;
            control_stalls += 2;
            total_stalls += 2;
            buf.invalid = true;
            ready = true;
            return buf;
        }
    else if(idexBuf.bneq)
        {
            control_instructions++;
            // buf.writeToRegister = false;
            //compare with 0
            int val1;
            if(!idexBuf.dest.valid) {
                //only possible in case of operand forwarding
                int tval = FU.request(idexBuf.dest.tag);
                if(FU.request_success)
                {
                    val1 = tval;
                    idexBuf.dest.data = val1;
                    idexBuf.dest.valid = true;
                }
                else
                {
                    //stall;
                    total_stalls++;
                    data_stalls++;
                    buf.invalid = true;
                    ready = false;
                    return buf;
                }
            }
            else
                val1 = idexBuf.dest.data;
            int val2 = 0;
            if(val1 == val2) {
                //calc effective address
                int val1 = idexBuf.npc;
                int val2 = idexBuf.jump_addr;
                val2 = (val2 << 1) & 0xff;
                int val = alu.adder(val1, val2, 0);
                buf.aluOutput = val;
                
                //set pc new value
                pc.write(val);
            // //generate go flush signal
            // FLUSH = true;
            // control_stalls += 2;
            // total_stalls += 2;
            // buf.invalid = true;
            // ready = true;
            // return buf;

            }
            else
            {
                //keep same pc value;
                pc.write(idexBuf.npc);
                // buf.invalid = true;
                // ready = true;
                // return buf;
            }

            //generate go flush signal
            total_instructions++;
            FLUSH = true;
            control_stalls += 2;
            total_stalls += 2;
            buf.invalid = true;
            ready = true;
            return buf;
        }
    else if (idexBuf.HALT_SIGNAL)
        {
            halt_instructions++;
            total_instructions++;
            buf.HALT_SIGNAL = true;
            buf.invalid = false;
            ready = false;
            idexBuf.invalid = true;
            return buf;
        }
        
    total_instructions++;
    buf.invalid = false;
    ready = true;
    return buf;
}
