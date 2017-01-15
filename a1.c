/*
	CIS 2750
	A1
	Author: Kushal Pandya
	Due Date: January 27 2017
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_LIMIT 20


int parseFile(FILE * file);
char ** createArray(int tokens);
int readArray(char ** array);



int main(int argc, char * argv[]) {

	char * fileName;
	int tokens;

	if (argc != 2) {
		printf("Not Enough Command Line arguments\n\n");
		fileName = "infile.cpp";
		// exit(0)
	}
	else fileName = argv[1];

	FILE *file = fopen(fileName, "r");
	tokens = parseFile(file);

	char ** array = createArray(tokens);
	readArray(array);
	fclose(file);

	return 0;
}



int parseFile(FILE * file) {

	int c;
	int tokens;

	// Helper file to store tokens for easier reading
	FILE * assetsFile = fopen("assets.txt", "w");

	// Booleans
	int lastCharNewLine = 0;
	int startQuote = 0;
	int dontPrintSpace = 0;

	// Counters
	int includeCounter = 0;
	int tokenCounter = 0;

	while ((c = fgetc(file)) != EOF) {

		if (startQuote == 1) {
			printf("%c", c);
			fprintf(assetsFile, "%c", c);
			if (c == '"') {
				startQuote = 0;
			}
		}
		else {
			switch(c) {
			case '"':
				startQuote = 1;
				printf("%c", c);
				fprintf(assetsFile, "%c", c);
				break;
			case '#':
				dontPrintSpace = 1;
				includeCounter++;
				printf("%c", c);
				fprintf(assetsFile, "%c", c);
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				if (dontPrintSpace == 0 && lastCharNewLine == 0) {
					printf("\n");
					fprintf(assetsFile, "\n");
					lastCharNewLine = 1;
					tokenCounter++;
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
				fprintf(assetsFile, "%c\n", c);
				lastCharNewLine = 1;
				tokenCounter++;
				break;
			default:
				printf("%c", c);
				fprintf(assetsFile, "%c", c);
				lastCharNewLine = 0;
				break;
			}
		}		
	}

	fclose(assetsFile);

	tokens = tokenCounter - includeCounter;
	printf("\n%d Tokens\n", tokens);
	return tokens;
}


char ** createArray(int tokens) {

	int i;
	char token[TOKEN_LIMIT];
	FILE * assetsFile = fopen("assets.txt", "r");
	
	char **tokenArray;
	tokenArray = malloc(sizeof(char*)*tokens);

	while(fgets(token, TOKEN_LIMIT, assetsFile) != NULL) {
		if (token[0] != '#')  {
			tokenArray[i] = malloc(sizeof(char)*(strlen(token)));
			strcpy(tokenArray[i], token);
			i++;
		}
	}

	fclose(assetsFile);
	return tokenArray;
}

int readArray(char ** array) {

	for (int i=0; i<35; i++) {
		printf("%s", array[i]);
	}

	return 0;
}