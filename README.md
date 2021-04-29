# PipelinedProcessorSimulator

This is a MIPS processor simulator.

This simulator works to demonstrate the working of a simple Pipelined Processor .
It implements two modes :- 1. Without operand forwarding 2. With operand forwarding
A single bit can be set in Processor.h to switch between the two modes .
The processor takes as input a ICacheData.txt and DCacheData.txt and runs the program with these instructions and data cache in a pipelined manner implementing stalls too .
