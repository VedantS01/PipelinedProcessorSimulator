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

int ICache::request(int addr) {
    int set = addr >> 2;
    int offset = addr & 3;
    int little = data[set].offset[offset];
    if(offset == 3) {
        offset = 0;
        set++;
        if(set >= 64) {
            set = 0;
        }
    }
    offset++;
    int big = data[set].offset[offset];
    int ret = big * 256;
    ret += little;
    return ret;
}