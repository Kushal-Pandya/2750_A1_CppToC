#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int findKeyWords(char * token, int startQuote) {

	if (startQuote == 0) {
		if (strcmp(token, "class\n") == 0) {
			return 2;
		}
		else if (strcmp(token, "{\n") == 0) {
			// printf("cdblock increment %s\n", token);
			return 7;
		}
		else if (strchr(token, ';')) {
			return 9;
		}
		else if (strchr(token, '(')) {
			return 6;
		}
	}

	return 0;
}


int main(int argc, char* argv[]) {
	int ch = 5;

	printf("%d\n", findKeyWords("testing(", 0));

	printf("test %d\n", ch);

	return 0;
}