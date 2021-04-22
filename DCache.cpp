/**
 *  ICache.cpp      :       Implements the class ICache
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Ashish Saboo
 * 
 *  NOTE            :       IN DEVELOPEMENT STAGE
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

int8 DCache::request(int8 addr) {
    int set = addr >> 2;
    int offset = addr & 3;
    int8 little = data[set].offset[offset];
    return little;
}

void DCache::write(int8 addr, int8 item){
    int set = addr >> 2;
    int offset = addr & 3;
    data[set].offset[offset] = item;
}