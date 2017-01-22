/*
	CIS 2750
	A1
	Author: Kushal Pandya
	Due Date: January 27 2017
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int parseFile(FILE * file);
char ** createArray(int tokens);
int readArray(char ** array, int size);
int freeArray(char ** array, int size);

int findKeyWords(char * token, int startQuote);
int compareTypes(char * token);


typedef struct List {
        char* value;
        struct List* next;
} List;


extern List* createList();
extern List* addValue(List* list, char* newValue);
extern void destroyList(List* list);

