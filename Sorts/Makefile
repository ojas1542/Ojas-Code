EXEC = sorting
CFLAGS=-std=c99 -Wall -Werror -Wextra -Wpedantic
CC=clang $(CFLAGS)

SOURCES = sorting.c binary.c shell.c quick.c bubble.c
OBJECTS = $(SOURCES:%.c=%.o)

.PHONY: all
all : $(EXEC)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LFLAGS)
sorting.o	: sorting.c
	$(CC) $(CFLAGS) -c sorting.c
binary.o	: binary.c
	$(CC) $(CFLAGS) -c binary.c
shell.o : shell.c
	$(CC) $(CFLAGS) -c shell.c
quick.o : quick.c
	$(CC) $(CFLAGS) -c quick.c
bubble.o : bubble.c
	$(CC) $(CFLAGS) -c bubble.c
format  :
	clang-format -i *.[ch]
clean	:
	rm -rf sorting sorting.o shell.o bubble.o quick.o binary.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind :
	valgrind --leak-check=full ./sorting
