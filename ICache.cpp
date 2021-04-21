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

int16 ICache::request(int8 addr) {
    int set = addr >> 2;
    int offset = addr & 3;
    int8 little = data[set].offset[offset];
    if(offset == 3) {
        offset = 0;
        set++;
        if(set >= 64) {
            set = 0;
        }
    }
    int8 big = data[set].offset[offset];
    return (big << 8) + little;
}