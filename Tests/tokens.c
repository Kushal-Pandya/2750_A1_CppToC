#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct myStruct {
	int a;};

int main(int argc, char* argv[]) {
	int ch;

	char string[3] = "a\"n";

	for (int i; i<strlen(string); i++) {
		switch(string[i]) {
			case 'a':
				printf("%c\n", string[i]);
				break;
			case 92:
				printf("%c FOUND\n", string[i]);
		}

		printf("%c\n", string[i]);
	}

	printf("Hello World!!\n");
	return 0;
}