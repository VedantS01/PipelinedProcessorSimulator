/**
 * 
 *  ForwardingUnit.cpp      :       Implementation of Register Forwarding Unit
 * 
 *  Version                 :       1.0
 * 
 *  AUTHOR                  :       Vedant Saboo, CS19B074
 * 
 ***/

#include <iostream>
#include "Processor.h"
using namespace std;

int ForwardingUnit::request(int tag) {
    //check in IDEX
    if(!IDEX.invalid)
    {
        if(IDEX.validsrc1 && IDEX.src1 == tag) 
        {
            request_success = true;
            return IDEX.srcval1;
        }
        if(IDEX.validsrc2 && IDEX.src2 == tag) 
        {
            request_success = true;
            return IDEX.srcval2;
        }
        if(IDEX.validdest && IDEX.dest == tag) 
        {
            request_success = true;
            return IDEX.destval;
        }
    }

    //check in EM
    if(!EM.invalid)
    {
        if(EM.validdest && EM.dest == tag) 
        {
            request_success = true;
            return EM.destval;
        }
    }
    

    //check in MW
    if(!MW.invalid)
    {
        if(MW.validdest && MW.dest == tag) 
        {
            request_success = true;
            return MW.destval;
        }
    }

    //else, not found
    request_success = false;
    return 0;
}