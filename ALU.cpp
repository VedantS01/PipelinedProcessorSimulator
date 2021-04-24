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
