#include <stdio.h>
#include <stdlib.h>

#include "a1.h"


List* createList(char * newValue) {

        List* newList = malloc(sizeof(List));
        if (newList != NULL) {
                newList->value = newValue;
                newList->next = NULL;
        }
        return newList;
}


List* addValue(List* list, char* newValue) {

        List* newList = createList(newValue);
        if (newList != NULL) {
                newList->next = list;
        }
        return newList;
}


void destroyList(List* list) {

        if (list->next != NULL) {
                destroyList(list->next);
        }
        free(list);
}


/*
int main(int argc, char** argv) {

        List* tokens = createList("");
        tokens = addValue(tokens, "World");
        tokens = addValue(tokens, "Licka");

        List* iter;
        for (iter=tokens; iter!=NULL; iter=iter->next) {
                printf("%s\n", iter->value);
        }

        destroyList(tokens);
        return 0;
}
*/