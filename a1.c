/*
	CIS 2750
	A1
	Author: Kushal Pandya
	Due Date: January 27 2017
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_LIMIT 25


int parseFile(FILE * file);
int createArray(int tokens);
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
	createArray(tokens);
	// readArray(array);
	fclose(file);

	return 0;
}



int parseFile(FILE * file) {

	int c;
	int tokens;

	// Helper file to store tokens for easier reading
	FILE * assetsFile = fopen("assets.txt", "w");

	// Booleans
	int lastCharSpace = 0; // Used to check if last char was a white space
	int lastCharNewLine = 0; // print newline if last char was newline
	int startQuote = 0; // Used to indicate start of quote
	int dontPrintSpace = 0; //Used for not printing space of includes
	int escapeChar = 0; // Indicates if last char was escape character

	int possComment = 0; // Possible start of a comment
	int endComment = 0; // possible end of comment
	int newComment = 0; // Used to indicate if start of comment
	int newMultiLineComment = 0;

	// Counters
	int includeCounter = 0;
	int tokenCounter = 0;

	while ((c = fgetc(file)) != EOF) {

		if (startQuote == 1) {
			lastCharSpace = 0;
			lastCharNewLine = 0;
			fprintf(assetsFile, "%c", c);

			if (c == '\\') escapeChar = 1;
			else if (escapeChar == 1 && c == '"') escapeChar = 0;
			else if (escapeChar == 0 && c == '"') startQuote = 0;
		} 
		else if (newComment == 1 || newMultiLineComment == 1) {
			lastCharSpace = 0;
			lastCharNewLine = 0;
			fprintf(assetsFile, "%c", c);

			if (c == '\n') newComment = 0;
			else if (c == '*' && newMultiLineComment == 1) endComment = 1;
			else if (c == '/' && endComment == 1 && newMultiLineComment == 1) {
				newMultiLineComment = 0;	
			} 
		}
		else {
			switch(c) {
			case '"':
				startQuote = 1;
				lastCharSpace = 0;
				lastCharNewLine = 0;
				possComment = 0;
				fprintf(assetsFile, "%c", c);
				break;
			case '#':
				dontPrintSpace = 1;
				lastCharNewLine = 0;
				lastCharSpace = 0;
				includeCounter++;
				possComment = 0;
				fprintf(assetsFile, "%c", c);
				break;
			case '\n':
				if (lastCharNewLine == 1) {
					fprintf(assetsFile, "\n");
				}
				lastCharNewLine = 1;
				newComment = 0; // a single line comment would end once new line is found
			case ' ':
			case '\t':
			case '\r':
				if (dontPrintSpace == 0 && lastCharSpace == 0) {
					fprintf(assetsFile, "\n");
					lastCharSpace = 1;
					tokenCounter++;
				}
				else dontPrintSpace = 0;
				possComment = 0;			
				break;
			case ',':
			case ';':
			case '(':
			case ')':
			case '{':
			case '}':
				fprintf(assetsFile, "%c\n", c);
				lastCharSpace = 1;
				lastCharNewLine = 0;
				possComment = 0;
				tokenCounter++;
				break;
			case '/':
				fprintf(assetsFile, "%c", c);
				if (possComment == 1) newComment = 1; // if possible comment, it is one now
				else possComment = 1; // else it may just be a possible comment
				break;
			case '*':
				fprintf(assetsFile, "%c", c);
				if (possComment == 1) newMultiLineComment = 1; // if there is a possible comment, there is one now
				else possComment = 1;
				break;
			default:
				fprintf(assetsFile, "%c", c);
				lastCharSpace = 0;
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


// Files below should be in list interface file

int createArray(int tokens) {

	printf("test");

	int i;
	char token[TOKEN_LIMIT];
	FILE * assetsFile = fopen("assets.txt", "r");
	
	char **tokenArray;
	tokenArray = malloc(sizeof(char*)*tokens);

	while(fgets(token, TOKEN_LIMIT, assetsFile) != NULL) {
		tokenArray[i] = malloc(sizeof(char)*(strlen(token)));
		strcpy(tokenArray[i], token);
		i++;
	}

	for (int i=0; i<tokens; i++) 
		printf("%s\n", tokenArray[i]);

	fclose(assetsFile);
	return 0;
	// return tokenArray;
}

int readArray(char ** array) {

	for (int i=0; i<35; i++) {
		printf("%s", array[i]);
	}

	return 0;
}
