#include "a1.h"

/* Linked List Library for functions*/

struct Func * createFuncList(char * type, char * name) {
	struct Func * newList = malloc(sizeof(struct Func));
	    if (newList != NULL) {
	    	newList->type = type;
            newList->name = name;
            newList->parameters = createVarList("", "", "");
            newList->contents = createList("");
            newList->variables = createVarList("", "", "");
            newList->next = NULL;
    }
    return newList;
}

struct Func * addFuncToList(struct Func * funcList, char *type, char * name) {
	struct Func* newList = createFuncList(type, name);
    if (newList != NULL) {
            newList->next = funcList;
    }
    return newList;
}

int checkIfFuncExists(struct Func * funcList, char *name) {
	struct Func * iter;
	for (iter=funcList; iter!=NULL; iter=iter->next) {
		if (strcmp(iter->name, name) == 0) return 1;
	}
	return 0;
}

void displayFuncList(struct Func * funcList) {
	struct Func * iter;
	for (iter=funcList; iter!=NULL; iter=iter->next) {
		printf("FuncType:%s FuncName:%s\n", iter->type, iter->name);

        printf("FuncParameters:\n");
        displayVarList(iter->parameters);
        printf("FuncVariables:\n");
        displayVarList(iter->variables);
        printf("FuncContents:\n");
        displayList(iter->contents);
    }
}


void destroyFuncList(struct Func * funcList) {
    if (funcList->next != NULL) {
            destroyFuncList(funcList->next);
    }
    free(funcList);
}


/*
Recursively stores the function parameters.
*/
int storeFuncParameters(char ** array, struct Func * funcList, int arrayIndex) {

    int i = arrayIndex;
    int newIndex;
    char * name = malloc(sizeof(char)*20);
    char * type = malloc(sizeof(char)*15);

    if (compareTypes(array[i])) {
        strcpy(type, array[i]);
        removeCharFromString(type, '\n');
        
        if (strchr(array[i+1], ',') != NULL) {
            strcpy(name, strtok(array[i+1], ","));
/*            printf("[[%s, %s]]\n", type, name);
*/          funcList->parameters = addVarToList(funcList->parameters, type, name, "");
            newIndex = storeFuncParameters(array, funcList, i+2);
        }
        else if (strcmp(array[i+2], ",\n") == 0) { /*Would it ever get to this else if (cause , in first if statement)*/
            strcpy(name, array[i+1]);
            removeCharFromString(name, '\n');
            funcList->parameters = addVarToList(funcList->parameters, type, name, "");
            newIndex = storeFuncParameters(array, funcList, i+3);  
        }
        else {
            if (strchr(array[i+1], ')') != NULL) 
                strcpy(name, strtok(array[i+1], ")"));
            else {
                strcpy(name, array[i+1]);
                removeCharFromString(name, '\n');
            }
            newIndex = i+2;
            funcList->parameters = addVarToList(funcList->parameters, type, name, "");
        }
    }
    return newIndex;
}


/*
Sequentially stores the function variables.
*/
int storeFuncVariables(char ** array, int arraySize, struct Func * funcList, int arrayIndex) {

    int i;
    int noMoreVars = 0;

    for (i=arrayIndex; i<arraySize; i++) {

        char * name = calloc(20, sizeof(char));
        char * type = malloc(sizeof(char)*15);
        char * value = malloc(sizeof(char)*40);

        if (compareTypes(array[i]) && noMoreVars == 0) {

            strcpy(type, array[i]);
            removeCharFromString(type, '\n');

            if (strcmp(array[i], "class\n") == 0) {

                /*strcpy(array[i], "struct\n");
                strcpy(type, array[i]);
                removeCharFromString(type, '\n');*/

                strcpy(name, array[i+1]);
                removeCharFromString(name, '\n');

                if (strchr(array[i+2], ';') != NULL) {
                    strcpy(value, strtok(array[i+2], ";"));
                    funcList->variables = addVarToList(funcList->variables, type, name, value);
                    i = i + 2;
                }
                else if (strcmp(array[i+3], ";\n") == 0) { 
                    strcpy(value, array[i+2]);
                    removeCharFromString(value, '\n');
                    funcList->variables = addVarToList(funcList->variables, type, name, value);
                    i = i + 3;
                }
                else if (strchr(array[i+2], ',') != NULL || strcmp(array[i+3], ",\n") == 0) {
                    int temp = storeMultiLineClassVars(array, arraySize, funcList, i, type, name);
                    i = temp;
                }
            }
            else if (strchr(array[i+1], ';') != NULL) {
                strcpy(name, strtok(array[i+1], ";"));
                funcList->variables = addVarToList(funcList->variables, type, name, "");
                i = i + 1;
            }
            else if (strcmp(array[i+2], ";\n") == 0) { 
                strcpy(name, array[i+1]);
                removeCharFromString(name, '\n');
                funcList->variables = addVarToList(funcList->variables, type, name, "");
                i = i + 1;
            }
            else if (strchr(array[i+1], ',') != NULL || strcmp(array[i+2], ",\n") == 0) {                
                int temp = storeMultiLineFuncVariables(array, arraySize, funcList, i, type);
                i = temp;
            }
            else if (strchr(array[i+1], '=') != NULL) {
                strcpy(name, strtok(array[i+1], "="));
                if (strchr(array[i+2], ';') != NULL) /*Just a confirmation check*/
                    strcpy(value, strtok(array[i+2], ";"));
                funcList->variables = addVarToList(funcList->variables, type, name, value);
                i = i + 2;
            }
            else if (strcmp(array[i+2], "=\n") == 0) {
                strcpy(name, array[i+1]);
                removeCharFromString(name, '\n');
                if (strchr(array[i+3], ';') != NULL) /*Just a confirmation check, NEED to watch out for _; _ being space*/
                    strcpy(value, strtok(array[i+2], ";"));
                funcList->variables = addVarToList(funcList->variables, type, name, value);
                i = i + 3;
            }
        }
        else if (strchr(array[i], '}') != NULL) {
            printf("END%s\n", array[i]);
            return i-1;
        }
        else {
            noMoreVars = 1;
            strcpy(name, array[i]);
            removeCharFromString(name, '\n');
            funcList->contents = addValue(funcList->contents, name);
        }
    }
    return i;
}


int storeMultiLineFuncVariables(char **array, int arraySize, struct Func *funcList, int arrayIndex, char * type) {
    int j;
    int i = arrayIndex;

    for (j=i+1; j<arraySize; j++) {

        char * name = calloc(20, sizeof(char));
        if (strchr(array[j], ',') != NULL) {
            strcpy(name, strtok(array[j], ","));
            funcList->variables = addVarToList(funcList->variables, type, name, ""); 
        }
        else if (strcmp(array[j+1], ",\n") == 0) {
            strcpy(name, array[j]);
            removeCharFromString(name, '\n'); 
            funcList->variables = addVarToList(funcList->variables, type, name, "");
            j = j + 1;
        }
        else if (strchr(array[j], ';') != NULL) {
            strcpy(name, strtok(array[j], ";")); 
            funcList->variables = addVarToList(funcList->variables, type, name, "");
            return j;
        }
        else if (strcmp(array[j+1], ";\n") == 0) {
            strcpy(name, array[j]);
            removeCharFromString(name, '\n');
            funcList->variables = addVarToList(funcList->variables, type, name, "");
            j = j + 1;
            return j;
        }
    }
    return i;   
}

int storeMultiLineClassVars(char **array, int arraySize, struct Func *funcList, int arrayIndex, char *type, char *name) {
    int j;
    int i = arrayIndex;

    for (j=i+2; j<arraySize; j++) {

        char * value = calloc(20, sizeof(char));
        if (strchr(array[j], ',') != NULL) {
            strcpy(value, strtok(array[j], ","));
            funcList->variables = addVarToList(funcList->variables, type, name, value); 
        }
        else if (strcmp(array[j+1], ",\n") == 0) {
            strcpy(value, array[j]);
            removeCharFromString(value, '\n'); 
            funcList->variables = addVarToList(funcList->variables, type, name, value);
            j = j + 1;
        }
        else if (strchr(array[j], ';') != NULL) {
            strcpy(value, strtok(array[j], ";")); 
            funcList->variables = addVarToList(funcList->variables, type, name, value);
            return j;
        }
        else if (strcmp(array[j+1], ";\n") == 0) {
            strcpy(value, array[j]);
            removeCharFromString(value, '\n');
            funcList->variables = addVarToList(funcList->variables, type, name, value);
            j = j + 1;
            return j;
        }
    }
    return i; 
}