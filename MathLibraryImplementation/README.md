# Purpose 

This program simulates the programmer's approximation of the sin,cos,tan and exp function. User must enter a program flag at the time of execution to select which function to simulate.

# Building

Typing "make" will build the code.
Typing "./math -"flag".
The "flag" can be either;
s for sin simulation; 
c for cos simulation; 
t for tan simulation; 
e for exp simulation; 
a for simulating all functions.
Only one flag will processed by the program at a time. If two flags are entered, the last flag to be entered will be processed.
Typing "make clean" will clean the directory of unnecessary binaries.
Typing "make all" will build all targets.
Typing "make infer" will run infer analyzer on the code to check for issues.
