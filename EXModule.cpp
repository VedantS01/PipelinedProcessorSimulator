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

struct EXBuffer EXModule::execute(IDEXBuffer idexbuf)
{
    if(idexbuf.arithmetic)   //mode=0
    {
          if( (subop>>1) & (subop&1) ) //subop=3
          {
              return inc(idexbuf);
          }
          else if( (subop>>1) & (!(subop&1)) ) //subop=2
          {
              return mul(idexbuf);
          }
          else if( (!(subop>>1)) & (subop&1)) //subop=1
          {
              return sub(idexbuf);
          }
          else //subop=0
          {
              return add(idexbuf);
          }
    }
    else if(idexbuf.logical)   //mode=1
    {
        if( (subop>>1) & (subop&1) ) //subop=3
        {
            return bitxor(idexbuf);
        }
        else if( (subop>>1) & (!(subop&1)) ) //subop=2
        {
            return bitnot(idexbuf);
        }
        else if( (!(subop>>1)) & (subop&1)) //subop=1
        {
            return bitor(idexbuf);
        }
        else //subop=0
        {
            return bitand(idexbuf);
        }
    }
    else if( (mode>>1) & (!(mode&1)) )  //mode=2
    {
        if(idexbuf.load)
        {
            return load(idexbuf);
        }
        else if(idexbuf.store)
        {
            return store(idexbuf);
        }
        else if(idexbuf.jump)
        {
            return jump(idexbuf);
        }
        else
        {
            return beqz(idexbuf);
        }
    }
    else
    {
        if(idexbuf.HALT_SIGNAL)
        {
            return HALT(idexbuf);
        }
    }
}
