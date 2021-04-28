/**
 *  ALU.cpp         :       ALU class implementation
 *
 *  Version         :       1.0
 *  Author          :       Parth Ajmera
 *
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
int ALU::AND(int a, int b) {
    return a & b;
}
int ALU::OR(int a, int b) {
    return a | b;
}
int ALU::NOT(int a) {
    return ~a;
}
int ALU::XOR(int a, int b) {
    return a ^ b;
}
