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
        printf("Class Name:%s \n", iter->name);

        printf("ClassVariables:\n");
        displayVarList(iter->variables);
        printf("ClassFunctions:\n");
        displayFuncList(iter->functions);   
    }
}

void destroyClassList(struct Class * classList) {
    if (classList->next != NULL) {
            destroyClassList(classList->next);
    }
    free(classList);
}

int storeClassVariables(char ** array, int arraySize, struct Class * classList, int arrayIndex) {

    int j;
    int i = arrayIndex;

    char * type = malloc(sizeof(char)*15);

    strcpy(type, array[i]);
    removeCharFromString(type, '\n');


    if (strchr(array[i+1], ';') != NULL) {
        char * name = calloc(20, sizeof(char));
        strcpy(name, strtok(array[i+1], ";")); 

        classList->variables = addVarToList(classList->variables, type, name, "");
        i = i + 1;
        return i;
    }
    else if (strchr(array[i+1], ',') != NULL || strcmp(array[i+2], ",\n") == 0) {

        for (j=i+1; j<arraySize; j++) {

            char * name = calloc(20, sizeof(char));
            if (strchr(array[j], ',') != NULL) {
                strcpy(name, strtok(array[j], ","));
                classList->variables = addVarToList(classList->variables, type, name, ""); 
            }
            else if (strcmp(array[j+1], ",\n") == 0) {
                strcpy(name, array[j]);
                removeCharFromString(name, '\n'); 
                classList->variables = addVarToList(classList->variables, type, name, "");
                j = j + 1;
            }
            else if (strchr(array[j], ';') != NULL) {
                strcpy(name, strtok(array[j], ";")); 
                classList->variables = addVarToList(classList->variables, type, name, "");
                return j;
            }
            else if (strcmp(array[j+1], ";\n") == 0) {
                strcpy(name, array[j]);
                removeCharFromString(name, '\n');
                classList->variables = addVarToList(classList->variables, type, name, "");
                j = j + 1;
                return j;
            }
        }
    }
    else if (strcmp(array[i+2], ";\n") == 0) {
        char * name = calloc(20, sizeof(char));
        strcpy(name, array[i+1]);
        removeCharFromString(name, '\n');

        classList->variables = addVarToList(classList->variables, type, name, "");
        i = i + 2;
        return i;
    }

    return i;
}
