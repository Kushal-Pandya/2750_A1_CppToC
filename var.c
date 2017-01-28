#include "a1.h"


/* Linked List Library for Variables*/

struct Var * createVarList(char * type, char * name, char * value) {
	struct Var * newList = malloc(sizeof(struct Var));
	if (newList != NULL) {
			newList->type = type;
            newList->name = name;
            newList->value = value;
            newList->next = NULL;
    }
    return newList;
}

struct Var * addVarToList(struct Var * varList, char * type, char * name, char * value) {
	struct Var* newList = createVarList(type, name, value);
    if (newList != NULL) {
            newList->next = varList;
    }
    return newList;
}

int checkIfVarExists(struct Var * varList, char *name) {
	struct Var * iter;
	for (iter=varList; iter!=NULL; iter=iter->next) {
		if (strcmp(iter->name, name) == 0) return 1;
	}
	return 0;
}

void displayVarList(struct Var * varList) {
	struct Var * iter;
	for (iter=varList; iter!=NULL; iter=iter->next) 
		printf("%s %s %s\n", iter->type, iter->name, iter->value);
}

void destroyVarList(struct Var * varList) {
    if (varList->next != NULL) {
            destroyVarList(varList->next);
    }
    free(varList);
}
