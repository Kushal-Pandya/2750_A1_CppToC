CC = gcc
CFLAGS = -Wall -ansi -g
LISTS_FILES = var.c func.c class.c list.c

A1: a1.o list.o
	$(CC) $(LISTS_FILES) $(CFLAGS) a1.o -o a1

a1.o: a1.c a1.h
	$(CC) $(CFLAGS) -c a1.c 

list.o: list.c a1.h
	$(CC) $(CFLAGS) -c list.c 

run:
	valgrind --leak-check=full --show-reachable=yes ./a1 infile.cpp

clean: 
	rm -f *.o a1 assets.txt