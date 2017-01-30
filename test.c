#include "a1.h"

char * printNthFromLast(struct List* list, int n)
{
    int len = 0, i;
    struct List* temp = list;
    char* toReturn = calloc(10, sizeof(char));
 
    len = getListSize(list);
 
    if (len < n)
      return toReturn;
 
    temp = list;
     for (i = 1; i < len-n+1; i++)
       temp = temp->next;
 
    strcpy(toReturn, temp->value);
 
    return toReturn;
}

int main(void) {

	List* tokens = createList("");
    tokens = addValue(tokens, "World");
    tokens = addValue(tokens, "Licka");

    printf("%s\n",printNthFromLast(tokens, 3));

    destroyList(tokens);
    return 0;


}

