# Purpose 

This program will find all paths from node A to Z given all possible interconnecting edges. User must enter a program flag at the time of execution to select for undirected or directed graph, the matrix to be printed and input via either file or console. 

# Building

Typing "make" will build the code.
Typing "./pathfinder -"flag(s)" will run it.
The "flag" can be either;
m for printing matrix; 
u for undirected graph; 
d for directed graph; 
i for input file;
If flag '-i' is used, it must follow the name of the text file that is to be used.  
The flags u and d are mutually exclusively. Only one can be used at once. Otherwise program ends with error. 
Typing "make clean" will clean the directory of unnecessary binaries.
Typing "make all" will build all targets.
Typing "make infer" will run infer analyzer on the code to check for issues.


In this program, running "make infer" will generate one error about dead storage because the pointer passed into the stack pop function isn't used but is just assigned to the popped value. This definition follows the API implementation suggested in the assignment pdf.
