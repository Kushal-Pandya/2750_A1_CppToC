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
	for (iter=funcList; iter!=NULL; iter=iter->next) 
		printf("%s %s\n", iter->type, iter->name);
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
struct Func * storeFuncParameters(char ** array, struct Func * funcList, int arrayIndex) {

    int i = arrayIndex;
    char * name = malloc(sizeof(char)*20);
    char * type = malloc(sizeof(char)*15);

    if (compareTypes(array[i])) {
        strcpy(type, array[i]);
        removeCharFromString(type, '\n');
        
        if (strchr(array[i+1], ',') != NULL) {
            strcpy(name, strtok(array[i+1], ","));
/*            printf("[[%s, %s]]\n", type, name);
*/            funcList->parameters = addVarToList(funcList->parameters, type, name, "");
            funcList = storeFuncParameters(array, funcList, i+2);
        }
        else if (strcmp(array[i+2], ",\n") == 0) {
            strcpy(name, array[i+1]);
            removeCharFromString(name, '\n');
            funcList->parameters = addVarToList(funcList->parameters, type, name, "");
            funcList = storeFuncParameters(array, funcList, i+3);  
        }
        else {
            if (strchr(array[i+1], ')') != NULL) 
                strcpy(name, strtok(array[i+1], ")"));
            else {
                strcpy(name, array[i+1]);
                removeCharFromString(name, '\n');
            }
            funcList->parameters = addVarToList(funcList->parameters, type, name, "");
        }
    }
    return funcList;
}