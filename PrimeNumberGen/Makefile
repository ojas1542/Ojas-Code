EXEC = sequence
CFLAGS=-O3 -Wall -Werror -Wextra -Wpedantic
CC=clang $(CFLAGS)
LFLAGS = -lm

SOURCES = sequence.c bv.c sieve.c
OBJECTS = $(SOURCES:%.c=%.o)

.PHONY: all
all : $(EXEC)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LFLAGS)
sequence.o	: sequence.c
	$(CC) $(CFLAGS) -c sequence.c
bv.o	: bv.c
	$(CC) $(CFLAGS) -c bv.c
sieve.o : sieve.c
	$(CC) $(CFLAGS) -c sieve.c
format  :
	clang-format -i *.[ch]
clean	:
	rm -rf sequence sequence.o bv.o sieve.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
