#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** createArray() {
	char ** array;
	array = malloc(sizeof(char*)*10);

	for (int i; i<20; i++) {
		array[i] = malloc(sizeof(char)*5);
		strcpy(array[i], "hi");
	}

	return array;
}


int main(int argc, char* argv[]) {
	int ch;

	char ** array = createArray();

	for (int i=0; i<35; i++) {
		printf("%s", array[i]);
	}

	return 0;
}