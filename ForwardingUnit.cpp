/**
 * 
 *  ForwardingUnit.cpp      :       Implementation of Register Forwarding Unit
 * 
 *  Version                 :       2.0
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
        if(IDEX.dest.valid && IDEX.dest.tag == tag) 
        {
            request_success = true;
            IDEX.dest.valid = false; //do not reference from here anymore
            return IDEX.dest.data;
        }
    }

    //check in EM
    if(!EM.invalid)
    {
        if(EM.validdest && EM.dest == tag) 
        {
            request_success = true;
            EM.validdest = false; //do not reference from here anymore
            return EM.destval;
        }
    }
    

    //check in MW
    if(!MW.invalid)
    {
        if(MW.validdest && MW.dest == tag) 
        {
            request_success = true;
            MW.validdest = false; //do not reference from here anymore
            return MW.destval;
        }
    }

    //else, not found
    request_success = false;
    return 0;
}

void ForwardingUnit::renderInvalidIfValid(int tag) {
    //check in IDEX
    if(!IDEX.invalid)
    {
        if(IDEX.dest.valid && IDEX.dest.tag == tag) 
        {
            IDEX.dest.valid = false; //do not reference from here anymore
        }
    }

    //check in EM
    if(!EM.invalid)
    {
        if(EM.validdest && EM.dest == tag) 
        {
            EM.validdest = false; //do not reference from here anymore
        }
    }
    

    //check in MW
    if(!MW.invalid)
    {
        if(MW.validdest && MW.dest == tag) 
        {
            MW.validdest = false; //do not reference from here anymore
        }
    }
}