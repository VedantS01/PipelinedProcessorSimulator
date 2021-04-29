# PipelinedProcessorSimulator

This is a MIPS processor simulator.

This simulator works to demonstrate the working of a simple Pipelined Processor .
It implements two modes :- 1. Without operand forwarding 2. With operand forwarding
A single bit can be set in Processor.h to switch between the two modes .
The processor takes as input a ICacheData.txt and DCacheData.txt and runs the program with these instructions and data cache in a pipelined manner implementing stalls too .

Steps to run the simulator :-

1. Write your code in assembly language
2. Use the compiler to get the ICache data and DCache data
3. Run make all
4. Run the ./simulator
5. Run the make clean command

After running the program , D$.out.txt will contain the Output Data .
Output.txt contains the values resulted by the simulator such as CPI , number of stalls , number of instructions , etc.

Developed and Presented by :-

1. CS19B071 - Sanchit Gupta (0xSanchit)
2. CS19B074 - Vedant Saboo (VedantS01)
3. CS19B065 - parth Ajmera
