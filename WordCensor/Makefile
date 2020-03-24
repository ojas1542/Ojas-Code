EXEC = newspeak
CFLAGS=-std=c99 -g -Wall -Werror -Wextra -Wpedantic -IprovidedCode
CC=clang $(CFLAGS)

SOURCES = newspeak.c ll.c hash.c bf.c bv.c gs.c parser.c speck.c
OBJECTS = $(SOURCES:%.c=%.o)

.PHONY: all
all : $(EXEC)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LFLAGS)
newspeak.o	: newspeak.c
	$(CC) $(CFLAGS) -c newspeak.c
ll.o	: ll.c
	$(CC) $(CFLAGS) -c ll.c
hash.o : hash.c
	$(CC) $(CFLAGS) -c hash.c
bf.o : bf.c
	$(CC) $(CFLAGS) -c bf.c
bv.c : bv.c
	$(CC) $(CFLAGS) -c bv.c
gs.o : gs.c
	$(CC) $(CFLAGS) -c gs.c
parser.o : parser.c
	$(CC) $(CFLAGS) -c parser.c
speck.o : speck.c
	$(CC) $(CFLAGS) -c speck.c
format  :
	clang-format -i *.[ch]
clean	:
	rm -rf sorting newpseak.o ll.c.o hash.o bf.o bv.o gs.o parser.o speck.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind :
	valgrind --leak-check=full ./newspeak
