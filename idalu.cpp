#include <iostream>
using namespace std;

string instruction[16];
int registerarray[16];

struct idbuffer
{
    string operation;
    int reg1;
    int reg2;
    int reg3;
};

struct exbuffer
{
    int targetreg;
    int targetvalue;
    bool flag=0;
};

void operationarrayinitialise()
{
    instruction[0]="ADD";
    instruction[1]="SUB";
    instruction[2]="MUL";
    instruction[3]="INC";
    instruction[4]="AND";
    instruction[5]="OR";
    instruction[6]="NOT";
    instruction[7]="XOR";
    instruction[8]="LOAD";
    instruction[9]="STORE";
    instruction[10]="JMP";
    instruction[11]="BEQZ";
    instruction[12]="null";
    instruction[13]="null";
    instruction[14]="null";
    instruction[15]="HLT";
}

void registerarrayinitialise()
{
    for(int i=0;i<16;i++)
    {
      registerarray[i]=i;
    }
}

struct exbuffer add(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg2 + idbuf.reg3};
}
struct exbuffer sub(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg2 - idbuf.reg3};
}
struct exbuffer mul(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg2 * idbuf.reg3};
}
struct exbuffer inc(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg1+1};
}
struct exbuffer binand(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg2 & idbuf.reg3};
}
struct exbuffer binor(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg2 | idbuf.reg3};
}
struct exbuffer binnot(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,~idbuf.reg1};
}
struct exbuffer binxor(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,idbuf.reg2 ^ idbuf.reg3};
}
struct exbuffer load(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,0};
}
struct exbuffer store(struct idbuffer idbuf)
{
    return exbuffer{idbuf.reg1,-1};
}
struct exbuffer jmp(struct idbuffer idbuf)
{
    return exbuffer{-2,-2};
}
struct exbuffer beqz(struct idbuffer idbuf)
{
    return exbuffer{-3,-3};
}
struct exbuffer hlt(struct idbuffer idbuf)
{
    return exbuffer{-4,-4};
}

struct idbuffer instructiondecode(int n)
{
    int dummy = n;
    int op3 = n%16;
    n/=16;
    int op2 = n%16;
    n/=16;
    int op1 = n%16;
    n/=16;
    int opcode = n%16;

    return idbuffer{instruction[opcode],registerarray[op1],registerarray[op2],registerarray[op3]};
}
struct exbuffer instructionexecute(struct idbuffer inst)
{
    if(inst.operation=="ADD")
    {
        return add(inst);
    }
    else if(inst.operation=="SUB")
    {
        return sub(inst);
    }
    else if(inst.operation=="MUL")
    {
        return mul(inst);
    }
    else if(inst.operation=="INC")
    {
        return inc(inst);
    }
    else if(inst.operation=="AND")
    {
        return binand(inst);
    }
    else if(inst.operation=="OR")
    {
        return binor(inst);
    }
    else if(inst.operation=="NOT")
    {
        return binnot(inst);
    }
    else if(inst.operation=="XOR")
    {
        return binxor(inst);
    }
    else if(inst.operation=="LOAD")
    {
        return load(inst);
    }
    else if(inst.operation=="STORE")
    {
        return store(inst);
    }
    else if(inst.operation=="JMP")
    {
        return jmp(inst);
    }
    else if(inst.operation=="BEQZ")
    {
        return beqz(inst);
    }
    else if(inst.operation=="HLT")
    {
        return hlt(inst);
    }
    else
    {
        cout <<"error"<<endl;
    }
}
void bufferwait()
{
  int i=10;
  while(i--)
  {
    ;
  }
}
long long int HexToDec(string hex)
{
    long long int dec = 0;
    for (auto i = hex.begin(); i != hex.end(); i++)
    {
        int deci = *i <= '9' ? *i - '0' : *i - 'a' + 10;
        dec = dec * 16 + deci;
    }
    return dec;
}
int main()
{
    while(true)
    {
      string s;
      cin >> s;
      long long int n=HexToDec(s);
      registerarrayinitialise();
      operationarrayinitialise();
      struct idbuffer idbuff=instructiondecode(n);
      bufferwait();
      struct exbuffer exbuff=instructionexecute(idbuff);
      cout<<exbuff.targetreg<<" "<<exbuff.targetvalue<<" "<<exbuff.flag<<endl;
    }
}

/**
 * END OF FILE
 **/
