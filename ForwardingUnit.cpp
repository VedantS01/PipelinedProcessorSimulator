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
        // if(IDEX.validsrc1 && IDEX.src1 == tag) 
        // {
        //     request_success = true;
        //     IDEX.validsrc1 = false; //do not reference from here anymore
        //     return IDEX.srcval1;
        // }
        // if(IDEX.validsrc2 && IDEX.src2 == tag) 
        // {
        //     request_success = true;
        //     IDEX.validsrc2 = false; //do not reference from here anymore
        //     return IDEX.srcval2;
        // }
        if(IDEX.validdest && IDEX.dest == tag) 
        {
            request_success = true;
            IDEX.validdest = false; //do not reference from here anymore
            return IDEX.destval;
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
        if(IDEX.validsrc1 && IDEX.src1 == tag) 
        {
            IDEX.validsrc1 = false; //do not reference from here anymore
        }
        if(IDEX.validsrc2 && IDEX.src2 == tag) 
        {
            IDEX.validsrc2 = false; //do not reference from here anymore
        }
        if(IDEX.validdest && IDEX.dest == tag) 
        {
            IDEX.validdest = false; //do not reference from here anymore
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