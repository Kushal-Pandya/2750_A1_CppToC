/*
	This program splits another program into tokens.
	It will split whitespace and punctuation.
	It will split string values
*/


#include <stdio.h>
#include <stdlib.h>



void parseFile(FILE * file) {

	int c;
	int lastCharNewLine = 0;
	char prevChar = ' ';
	int startQuote = 0;
	int dontPrintSpace = 0;

	while ((c = fgetc(file)) != EOF) {

		if (startQuote == 1) {
			printf("%c", c);
			if (c == '"') {
				startQuote = 0;
			}
		}
		else {
			switch(c) {
			case '"':
				startQuote = 1;
				printf("%c", c);
				break;
			case '#':
				dontPrintSpace = 1;
				printf("%c", c);
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				if (dontPrintSpace == 0 && lastCharNewLine == 0) {
					printf("\n");
					lastCharNewLine = 1;
					// if (c == '\n') prevChar = '\n';
				}
				else dontPrintSpace = 0;			
				break;
			case ',':
			case ';':
			case '(':
			case ')':
			case '{':
			case '}':
				printf("%c\n", c);
				lastCharNewLine = 1;
				break;
			default:
				printf("%c", c);
				lastCharNewLine = 0;
				break;
			}
		}		
	}
}


int main(int argc, char * argv[]) {

	char * fileName;

	if (argc != 2) {
		printf("Not Enough Command Line arguments\n\n");
		fileName = "tokens.c";
	}
	else fileName = argv[1];

	FILE *file = fopen(fileName, "r");
	parseFile(file);
	fclose(file);

	return 0;
}