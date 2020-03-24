# Purpose 

This program will compress a given text file or text input using LZ-78 algorithm. It will also display compression statistics.

BitVector ADT from asgn4 was used in this assignment.

# Building

Typing "make" or "make all" will build the code.
Typing "./encode -"flag(s)" will run the compression algorithm.
The encode program will take the following flags:
v for to show compression statistics; 
i for inputting file to compress;
o for specifying output file;
Typing "./decode -"flag(s)" decompress the file
The decode program will take the following flags:
v for to show decompression statistics;
i for inputing file to decompress
o for file to put decompressed input into
Typing "make clean" will clean the directory of unnecessary binaries.
Typing "make all" will build all targets.
Typing "make infer" will run infer analyzer on the code to check for issues.
Typing "make valgrind" will run valgrind analyzer to check for memory leaks.
Typing "make format" will run clang format on C files.

Note about infer errors: There were 2 resouce leaks in encode.c for not freeing memory for input and output files when open is called. However, both input and output files were freed with the close function in the same scope. 

