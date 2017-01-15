/*
	CIS 2750
	A1
	Author: Kushal Pandya
	Due Date: January 27 2017
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseFile(FILE * file) {

	int c;
	int lastCharNewLine = 0;
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
		fileName = "infile.cpp";
	}
	else fileName = argv[1];

	FILE *file = fopen(fileName, "r");
	parseFile(file);
	fclose(file);

	return 0;
}