# Purpose 

This program will find words from a file and will either say that they're forbidden or need translation. The words chosen by the filter and hashtable are based on reading two text files with words to censor.
# Building

Typing "make" or "make all" will build the code.
Typing "./sorting -"flag(s)" will run it.
The "flag" can be a combination of;
b for no move to front; 
m for move to front;
f for setting bloomfilter size;
h for hast table size;
s to not run filter.
Cannot pass both -m and -b flags.
Typing "make clean" will clean the directory of unnecessary binaries.
Typing "make all" will build all targets.
Typing "make infer" will run infer analyzer on the code to check for issues.
Typing "make valgrind" will run valgrind analyzer to check for memory leaks.


