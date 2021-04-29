g++ *.cpp -o sim
#g++ Simulator.cpp Processor.cpp ICache.cpp IFIDBuffer.cpp IFModule.cpp DCache.cpp PC.cpp Register.cpp ALU.cpp EMBuffer.cpp EXModule.cpp IDEXBuffer.cpp IDRFModule.cpp MEMModule.cpp MWBuffer.cpp WBModule.cpp ForwardingUnit.cpp -o simulator
./sim
rm sim