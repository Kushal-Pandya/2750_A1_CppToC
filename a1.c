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

#define TOKEN_LIMIT 100


int parseFile(FILE * file);
char ** createArray(int tokens);
int readArray(char ** array, int size);
int freeArray(char ** array, int size);


int main(int argc, char * argv[]) {

	char * fileName;
	int tokens;

	if (argc != 2) {
		printf("Not Enough Command Line arguments\n\n");
		fileName = "infile.cpp";
		// exit(0)
	}
	else fileName = argv[1];

	// Check if file exists
	if (access(fileName, F_OK) == -1) {
		printf("File doesn't exist or error opening\n");
		exit(0);
	}

	FILE *file = fopen(fileName, "r");
	tokens = parseFile(file);

	char ** array = createArray(tokens);
	readArray(array, tokens);

	freeArray(array, tokens);

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

	int possEscapeChar = 0; //Possibility of escape character in string
	int escapeChar = 0; // Indicates if last char was escape character

	int possComment = 0; // Possible start of a comment
	int endComment = 0; // possible end of comment
	int newComment = 0; // Used to indicate if start of comment
	int newMultiLineComment = 0;

	// Counters
	int tokenCounter = 0;

	while ((c = fgetc(file)) != EOF) {

		if (startQuote == 1) {
			lastCharSpace = 0;
			lastCharNewLine = 0;
			fprintf(assetsFile, "%c", c);

			if (c == '\n') {        // Need to take into account that strings may be more than 1 line?
				lastCharNewLine = 1;
				tokenCounter++;
			} 

			if (c == '\\') possEscapeChar = 1;
			else if (c == '"'){
				if (possEscapeChar == 1) escapeChar = 1;
				else if (escapeChar == 0) startQuote = 0;
			} 
			else { 
				possEscapeChar = 0;
				escapeChar = 0;
			}
		} 
		else if (newComment == 1 || newMultiLineComment == 1) {
			lastCharSpace = 0;
			lastCharNewLine = 0;
			fprintf(assetsFile, "%c", c);

			if (c == '\n') { 
				newComment = 0;
				tokenCounter++;
				if (newMultiLineComment == 0) lastCharNewLine = 1;
			}
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
				lastCharNewLine = 0;
				lastCharSpace = 0;
				possComment = 0;
				fprintf(assetsFile, "%c", c);
				break;
			case '\n':
				if (lastCharNewLine == 1) {
					fprintf(assetsFile, "\n");
					tokenCounter++;
				}
				lastCharNewLine = 1;
				newComment = 0; // a single line comment would end once new line is found
			case ' ':
			case '\t':
			case '\r':
				if (lastCharSpace == 0) {
					fprintf(assetsFile, "\n");
					lastCharSpace = 1;
					tokenCounter++;   
				}
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
				lastCharSpace = 0;
				lastCharNewLine = 0;
				break;
			case '*':
				fprintf(assetsFile, "%c", c);
				if (possComment == 1) newMultiLineComment = 1; // if there is a possible comment, there is one now
				else possComment = 1;
				lastCharSpace = 0;
				lastCharNewLine = 0;
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

	tokens = tokenCounter;
	printf("\n%d Tokens\n", tokens);
	return tokens;
}


// Files below should be in list interface file

char ** createArray(int tokens) {

	int i;
	char *token = calloc(TOKEN_LIMIT, sizeof(char));
	FILE * assetsFile = fopen("assets.txt", "r");
	
	char **tokenArray;
	tokenArray = malloc(sizeof(char*)*tokens);

	while(fgets(token, TOKEN_LIMIT, assetsFile) != NULL) {
		tokenArray[i] = malloc(sizeof(char)*(strlen(token)+1));
		strcpy(tokenArray[i], token);
		i++;
	}

	fclose(assetsFile);
	return tokenArray;
}


int readArray(char ** array, int size) {

	for (int i=0; i<size; i++) 
		printf("%s", array[i]);

	return 0;
}


int freeArray(char ** array, int size) {

	for (int i=0; i<size; i++) 
		free(array[i]);

	free(array);
	return 0;
}