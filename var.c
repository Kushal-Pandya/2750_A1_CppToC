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
		printf("VarType:%s VarName:%s VarValue:%s\n", iter->type, iter->name, iter->value);
}

void destroyVarList(struct Var * varList) {
    if (varList->next != NULL) {
            destroyVarList(varList->next);
    }
    free(varList);
}

struct Var * storeMultiLineVars(char **array, int arraySize, struct Var *varList, int *arrayIndex, char *type, char *name) {
    int j;
    int i = *arrayIndex;

    for (j=i+2; j<arraySize; j++) {

        char * value = calloc(20, sizeof(char));
        if (strchr(array[j], ',') != NULL) {
            strcpy(value, strtok(array[j], ","));
            varList = addVarToList(varList, type, name, value); 
        }
        else if (strcmp(array[j+1], ",\n") == 0) {
            strcpy(value, array[j]);
            removeCharFromString(value, '\n'); 
            varList = addVarToList(varList, type, name, value);
            j = j + 1;
        }
        else if (strchr(array[j], ';') != NULL) {
            strcpy(value, strtok(array[j], ";")); 
            varList = addVarToList(varList, type, name, value);
            *arrayIndex = j;
            return varList;
        }
        else if (strcmp(array[j+1], ";\n") == 0) {
            strcpy(value, array[j]);
            removeCharFromString(value, '\n');
            varList = addVarToList(varList, type, name, value);
            j = j + 1;
            *arrayIndex = j;
            return varList;
        }
    }
    return varList; 
}

struct Var* storeGlobalVariables(char ** array, int arraySize, struct Var *varList, int* arrayIndex) {

    int j;
    int i = *arrayIndex;

    char * type = malloc(sizeof(char)*15);

    strcpy(type, array[i]);
    removeCharFromString(type, '\n');

    if (strchr(array[i+1], ';') != NULL) {
        char * name = calloc(20, sizeof(char));
        strcpy(name, strtok(array[i+1], ";")); 

        varList = addVarToList(varList, type, name, "");
        i = i + 1;
        *arrayIndex = i;
        return varList;
    }
    else if (strchr(array[i+1], ',') != NULL || strcmp(array[i+2], ",\n") == 0) {

        for (j=i+1; j<arraySize; j++) {

            char * name = calloc(20, sizeof(char));
            if (strchr(array[j], ',') != NULL) {
                strcpy(name, strtok(array[j], ","));
                varList = addVarToList(varList, type, name, ""); 
            }
            else if (strcmp(array[j+1], ",\n") == 0) {
                strcpy(name, array[j]);
                removeCharFromString(name, '\n'); 
                varList = addVarToList(varList, type, name, "");
                j = j + 1;
            }
            else if (strchr(array[j], ';') != NULL) {
                strcpy(name, strtok(array[j], ";")); 
                varList = addVarToList(varList, type, name, "");
                *arrayIndex = j;
                return varList;
            }
            else if (strcmp(array[j+1], ";\n") == 0) {
                strcpy(name, array[j]);
                removeCharFromString(name, '\n');
                varList = addVarToList(varList, type, name, "");
                j = j + 1;
                *arrayIndex = j;
                return varList;
            }
        }
    }
    else if (strcmp(array[i+2], ";\n") == 0) {
        char * name = calloc(20, sizeof(char));
        strcpy(name, array[i+1]);
        removeCharFromString(name, '\n');

        varList = addVarToList(varList, type, name, "");
        i = i + 2;
        *arrayIndex = i;
        return varList;
    }

    return varList;
}