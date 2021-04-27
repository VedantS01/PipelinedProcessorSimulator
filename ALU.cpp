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

int ALU::adder(int a, int b, bool as) {
    int r;
    if(as) {
        r = a - b;
    } else {
        r = a + b;
    }
    return r & 0xff;
}
int ALU::mul(int a, int b) {
    int r = a * b;
    return r & 0xff;
}
int ALU::and(int a, int b) {
    return a & b;
}
int ALU::or(int a, int b) {
    return a | b;
}
int ALU::not(int a) {
    return ~a;
}
int ALU::xor(int a, int b) {
    return a ^ b;
}
/*

struct EXBuffer add(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 + idexbuf.srcval2};
}
struct EXBuffer sub(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 - idexbuf.srcval2};
}
struct EXBuffer mul(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 * idexbuf.srcval2};
}
struct EXBuffer inc(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.destval+1};
}
struct EXBuffer bitand(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 & idexbuf.srcval2};
}
struct EXBuffer bitor(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 | idexbuf.srcval2};
}
struct EXBuffer bitnot(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, ~idexbuf.destval};
}
struct EXBuffer bitxor(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 ^ idexbuf.srcval2};
}

//LOGICAL ALU's - check once
struct EXBuffer load(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.dest, idexbuf.srcval1 + idexbuf.offset};
}
struct EXBuffer store(IDEXBuffer idexbuf)
{
    return EXBuffer{idexbuf.srcval1 + idexbuf.offset , indexbuf.dest};  //CONFUSED B/W DESTVAL,DEST ADDRESS
}
struct EXBuffer jmp(IDEXBuffer idexbuf)
{
    return EXBuffer{1,1};
    //TO BE COMPLETED
}
struct EXBuffer beqz(IDEXBuffer idexbuf)
{
    return EXBuffer{1,1};
    //TO BE COMPLETED
}
struct EXBuffer HALT(IDEXBuffer idexbuf)
{
    return EXBuffer{1,1};
    //TO BE COMLETED
}

*/
