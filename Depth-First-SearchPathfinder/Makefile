EXEC = pathfinder
CFLAGS=-O3 -Wall -Werror -Wextra -Wpedantic
CC=clang $(CFLAGS)

SOURCES = pathfinder.c stack.c
OBJECTS = $(SOURCES:%.c=%.o)

.PHONY: all
all : $(EXEC)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LFLAGS)
pathfinder.o	: pathfinder.c
	$(CC) $(CFLAGS) -c pathfinder.c
stack.o	: stack.c
	$(CC) $(CFLAGS) -c stack.c
format  :
	clang-format -i *.[ch]
clean	:
	rm -rf pathfinder pathfinder.o stack.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
