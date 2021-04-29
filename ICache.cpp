/**
 *  ICache.cpp      :       Implements the class ICache
 * 
 *  Version         :       1.0
 *  Author          :       Vedant Saboo (CS19B074)
 * 
 * 
 **/

#include "Processor.h"
#include <iostream>
using namespace std;

int ICache::request(int addr)
{
    int set = addr >> 2;
    int offset = addr & 3;
    int little = data[set].offset[offset];
    if (offset == 3)
    {
        offset = 0;
        set++;
        if (set >= 64)
        {
            set = 0;
        }
    }
    offset++;
    int big = data[set].offset[offset];
    int ret = little * 256;
    ret += big;
    return ret;
}

// void ICache::write(int addr, int item) {
//     int set = addr >> 2;
//     int offset = addr & 3;
//     data[set].offset[offset] = item >> 8;
//     data[set].offset[offset] = item & 0xff;
// }