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

#include "a1.h"

#define TOKEN_LIMIT 100


int main(int argc, char * argv[]) {

	char * fileName;
	int tokens;

	if (argc != 2) {
		printf("Not Enough Command Line arguments\n\n");
		fileName = "infile.cpp";
		/* exit(0)*/
	}
	else fileName = argv[1];

	/* Check if file exists */
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

	/* Helper file to store tokens for easier reading */
	FILE * assetsFile = fopen("assets.txt", "w");

	/* Booleans*/
	int lastCharSpace = 0; /* Used to check if last char was a white space*/
	int lastCharNewLine = 0; /* print newline if last char was newline*/
	int startQuote = 0; /* Used to indicate start of */

	int possEscapeChar = 0; /*Possibility of escape character in string*/
	int escapeChar = 0; /* Indicates if last char was escape character*/

	int possComment = 0; /* Possible start of a comment*/
	int endComment = 0; /* possible end of comment*/
	int newComment = 0; /* Used to indicate if start of comment*/
	int newMultiLineComment = 0;

	/* Counters*/
	int tokenCounter = 0;

	while ((c = fgetc(file)) != EOF) {

		if (startQuote == 1) {
			lastCharSpace = 0;
			lastCharNewLine = 0;
			fprintf(assetsFile, "%c", c);

			if (c == '\n') {        /* Need to take into account that strings may be more than 1 line?*/
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
				newComment = 0; /* a single line comment would end once new line is found*/
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
				if (possComment == 1) newComment = 1; /* if possible comment, it is one now*/
				else possComment = 1; /* else it may just be a possible comment*/
				lastCharSpace = 0;
				lastCharNewLine = 0;
				break;
			case '*':
				fprintf(assetsFile, "%c", c);
				if (possComment == 1) newMultiLineComment = 1; /* if there is a possible comment, there is one now*/
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


/* Files below should be in list interface file*/

char ** createArray(int tokens) {

	int i;
	char *token = calloc(TOKEN_LIMIT, sizeof(char));
	FILE * assetsFile = fopen("assets.txt", "r");
	
	char **tokenArray = malloc(sizeof(char*)*tokens);

	while(fgets(token, TOKEN_LIMIT, assetsFile) != NULL) {
		tokenArray[i] = malloc(sizeof(char)*(strlen(token)+1));
		strcpy(tokenArray[i], token);
		i++;
	}

	free(token);
	fclose(assetsFile);
	return tokenArray;
}


int readArray(char ** array, int size) {

	int isClass = 0; /* to get the class name*/
	int codeBlocks = 0; /* how many nested codeBlocks*/

	int possFunc = 0; /* Enabled when a class starts*/
	int confirmFunc = 0; /* Enabled when function starts*/

	char * className = calloc(10, sizeof(char));
	char * temp = calloc(20, sizeof(char));
	char * temp2 = calloc(20, sizeof(char));

	int i;
	for (i=0; i<size; i++) {

		if (strcmp(array[i], "class\n") == 0) {
			strcpy(array[i], "struct\n");
			isClass = 1;
		}
		else if (isClass) {
			/* store class name here*/
			strncpy(className, array[i], strlen(array[i])-1);
			isClass = 0;	
		}

		if (strcmp(array[i], "{\n") == 0) {
			codeBlocks++; 
			isClass = 0;	
		} 
		else if (strcmp(array[i], "}\n") == 0) codeBlocks--; 
		else if (strstr(array[i], "(\n") != NULL && codeBlocks == 1) {

			if (strchr(array[i], '.') != NULL) {
				char * varName = strtok(array[i], ".");
				char * token = strtok(NULL, ".");

				strcpy(temp2, token);
				strcat(varName, ".");
				strcpy(temp, className);
				strcat(temp, temp2);
				strcat(varName, temp);
				strcpy(array[i], varName);
			}
			else {
				strcpy(temp, className);
				strcat(temp, array[i]);
				strcpy(array[i], temp);
			}
		}

		printf("%d %d %s %s", codeBlocks, isClass, className, array[i]);
	}

	/* Testing printing
	for (int i=0; i<size; i++)
	printf("%s", array[i]); */


	return 0;
}

/*
	Returns:
	0 if only newline is found

	2 if class found
	3 if class name found
	4 if typefound
	5 if var name found
	6 if func found "("
	7 if brace/new code block found "{"
	8 if ending block found "}"
	9 if semicolon found ";"
	10 if something and punc is found "a;" MAYBE
*/
int findKeyWords(char * token, int startQuote) {

	if (startQuote == 0) {
		if (strcmp(token, "class\n") == 0) {
			return 2;
		}
		else if (strcmp(token, "{\n") == 0) {
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

int freeArray(char ** array, int size) {

	int i;
	for (i=0; i<size; i++) 
		free(array[i]);

	free(array);
	return 0;
}