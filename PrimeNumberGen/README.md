# Purpose 

This program will find all primes between 0 and a positive number of the user's choice. It will also print if any of those primes are fibonacci, lucas or mersenne numbers. It will also print if those number have palidromes in either base 2, base 10, base 14 or base 31.
Used BitVector ADT from asgn4.
# Building

Typing "make" or "make all" will build the code.
Typing "./sequence -"flag(s)" will run it.
The "flag" can be either;
s for printing primes; 
p for printing palindromic primes in given bases; 
n for passing in the number till which primes should be generated; 
If flag '-n' is used, it must be followed by a positive integer.
Typing "make clean" will clean the directory of unnecessary binaries.
Typing "make all" will build all targets.
Typing "make infer" will run infer analyzer on the code to check for issues.
