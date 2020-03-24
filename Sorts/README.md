# Purpose 

This program will sort an array of random numbers using Quick sort, Bubble sort, Binary-insertion sort and shell sort. The number of swaps and comparison between to elements will be counted as well.

# Building

Typing "make" or "make all" will build the code.
Typing "./sorting -"flag(s)" will run it.
The "flag" can be a combination of;
b for bubble sort; 
i for binary insertion sort;
q for quick sort;
s for shell sort;
A for all sorts above.
NOTE: One of the flags mentioned above MUST be used for output to be generated;
p followed by a positive number to print that amount of sorted elements starting from leftmost value;
r followed by a positive seed value so program can be made deterministic for testing purposes.
n followed by a positive number that indicates size of array to be sorted. 
Typing "make clean" will clean the directory of unnecessary binaries.
Typing "make all" will build all targets.
Typing "make infer" will run infer analyzer on the code to check for issues.
Typing "make valgrind" will run valgrind analyzer to check for memory leaks.
