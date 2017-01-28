#include "a1.h"


/* Linked List Library for classes*/

struct Class * createClassList(char * name) {
    struct Class* newList = malloc(sizeof(struct Class));
    if (newList != NULL) {
            newList->name = name;
            newList->variables = createVarList("", "", "");
            newList->functions = createFuncList("", "");
            newList->next = NULL;
    }
    return newList;
}

struct Class * addClassToList(struct Class *classList, char * name) {
    struct Class* newList = createClassList(name);
    if (newList != NULL) {
            newList->next = classList;
    }
    return newList;
}

int checkIfClassExists(struct Class * classList, char *name) {
	struct Class * iter;
	for (iter=classList; iter!=NULL; iter=iter->next) {
		if (strcmp(iter->name, name) == 0) return 1;
	}
	return 0;
}

void displayClassList(struct Class * classList) {
	struct Class * iter;
	for (iter=classList; iter!=NULL; iter=iter->next) {
        printf("Name:%s \n", iter->name);
    }
}

void destroyClassList(struct Class * classList) {
    if (classList->next != NULL) {
            destroyClassList(classList->next);
    }
    free(classList);
}

