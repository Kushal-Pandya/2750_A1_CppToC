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


void displayList(List * list) {
    List* iter;
    for (iter=list; iter!=NULL; iter=iter->next) {
         printf("%s\n", iter->value);
    }
}

void displayListReverse(List *list) {
    if (list != NULL) {
        displayListReverse(list->next);
        printf("%s\n", list->value);
    }
}

char *getListNode(List *list) {
    List *temp = list;
    List *t;
    char *toReturn = malloc(sizeof(char)*500);
    while(temp->next != NULL) {
        t=temp;
        temp=temp->next;
    }
    strcpy(toReturn, t->value);
    free(t->next);
    t->next = NULL;
    return toReturn;
}

int getListSize(List *list) {
    List * temp = list;
    int size = 0;

    while (temp != NULL) {
        ++size;
        temp = temp->next;
    }
    return size;
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