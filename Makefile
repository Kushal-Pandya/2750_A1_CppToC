CC = gcc
CFLAGS = -Wall -ansi -std=c99 -g

all: a1.o list.o
	$(CC) $(CFLAGS) a1.o list.o -o a1

a1.o: a1.c
	$(CC) $(CFLAGS) -c a1.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

clean: 
	rm -f *.o a1 assets.txt