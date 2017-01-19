#include <stdio.h>
#include <stdlib.h>


typedef struct Token {
        char* value;
        int numSpaces;
        struct Token* next;
} Token;


Token* createTokens(char* token, int spaces) {

        Token* newTokens = malloc(sizeof(Token));
        if (NULL != newTokens){
                newTokens->value = token;
                newTokens->numSpaces = spaces;
                newTokens->next = NULL;
        }
        return newTokens;
}


Token* addToken(Token* tokensList, char* token, int spaces) {

        Token* newTokens = createTokens(token, spaces);
        if (NULL != newTokens) {
                newTokens->next = tokensList;
        }
        return newTokens;
}


void removeTokens(Token* tokensList) {

        if (NULL != tokensList->next) {
                removeTokens(tokensList->next);
        }
        free(tokensList);
}



// int main(int argc, char** argv) {

//         Token* tokens = createTokens("Hello", 3);
//         tokens = addToken(tokens, "World", 2);
//         tokens = addToken(tokens, "Licka", 4);

//         Token* iter;
//         for (iter=tokens; NULL!=iter; iter=iter->next) {
//                 printf("%s %d\n", iter->value, iter->numSpaces);
//         }

//         removeTokens(tokens);
//         return 0;
// }