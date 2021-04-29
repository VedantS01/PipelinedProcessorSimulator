# PipelinedProcessorSimulator

## This is a MIPS processor simulator.

This simulator works to demonstrate the working of a simple Pipelined Processor .

It implements two modes :- 1. Without operand forwarding 2. With operand forwarding

A single bit can be set in Processor.h to switch between the two modes .

The processor takes as input a ICacheData.txt and DCacheData.txt and runs the program with these instructions and data cache in a pipelined manner implementing stalls too .

### Steps to run the simulator :-

1. Place your instructions in proper format in ICacheData.txt, a byte in every line.

2. Place DCache data in DCachaData.txt and contents of register file in RegisterData.txt

3. Run make all

4. Run the ./Simulator

5. Run the make clean command

After running the program , D$.out.txt will contain the Output Data .

Output.txt contains the values resulted by the simulator such as CPI , number of stalls , number of instructions , etc.

An additional file RF.out.txt will contain the updated register data.

### Developed and Presented by :-

1. CS19B074 - Vedant Saboo (VedantS01)

2. CS19B071 - Sanchit Gupta (0xSanchit)

3. CS19B065 - parth Ajmera
