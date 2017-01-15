CC = gcc
CFLAGS = -Wall -ansi -std=c99 -g

all: a1.o 
	$(CC) $(CFLAGS) a1.o -o a1

a1.o: a1.c
	$(CC) $(CFLAGS) -c a1.c

clean: 
	rm -f *.o a1