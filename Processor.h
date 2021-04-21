/**
 *  Processor.h     :       H file for the simulator
 * 
 *  NOTE            :       DEVELOPEMENT STAGE
 **/

class Register {

};

class RegisterFile {

};

class ICache {

};

class DCache {

};

class IFIDBuffer {

};

class IFModule {
    public:             //in deveopement phase, let's keep everything public. We can introduce data hidinglater on.
    Register pc;
    IFIDBuffer execute(/* args */);
};

class IDEXBuffer {

};

class IDRFModule {
    public:
    RegisterFile rf;
    IFIDBuffer ifidBuf;
    IDEXBuffer execute(/* args */);
};

class EMBuffer {

};

class ALU {

};

class EXModule {
    public:
    ALU alu;
    IDEXBuffer idexBuf;
    EMBuffer execute(/* args */);
};

class MWBuffer {
    
};

class MEMModule {
    public:
    DCache D$;
    EMBuffer emBuf;
    MWBuffer execute(/* args */);
};

class WBModule {
    public:
    MWBuffer mwBuf;
    void execute(/* args */);
};

class ControlUnit {

};

class Processor {
    public:
    ControlUnit CU;
    ICache I$;
    DCache D$;
    RegisterFile rf;
    //more data

    //methods
    
};