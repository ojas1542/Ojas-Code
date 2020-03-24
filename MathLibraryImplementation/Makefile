EXEC = math
CFLAGS=-O3 -Wall -Werror -Wextra -Wpedantic
CC=clang $(CFLAGS)
LFLAGS = -lm

SOURCES = math.c
OBJECTS = $(SOURCES:%.c=%.o)

.PHONY: all
all : $(EXEC)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LFLAGS)
#math :   math.o
#	$(CC) $(LFLAGS) -o math math.c
math.o	: math.c
	$(CC) $(CFLAGS) -c math.c
format  :
	clang-format -i *.[ch]
clean	:
	rm -rf math math.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
