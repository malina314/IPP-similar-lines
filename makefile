CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all clean

all: similar_lines

similar_lines: $(OBJECTS)
	$(CC) $(CFLAGS) -o similar_lines $(OBJECTS)

main.o: main.c vector.h lineVector.h readInput.h compare.h
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

lineVector.o: lineVector.c lineVector.h vector.h
	$(CC) $(CFLAGS) -c lineVector.c

compare.o: compare.c compare.h line.h lineVector.h vector.h
	$(CC) $(CFLAGS) -c compare.c

line.o: line.c line.h vector.h
	$(CC) $(CFLAGS) -c line.c

parse.o: parse.c parse.h line.h
	$(CC) $(CFLAGS) -c parse.c

readInput.o: readInput.c readInput.h parse.h line.h lineVector.h
	$(CC) $(CFLAGS) -c readInput.c

clean:
	rm -f similar_lines *.o
