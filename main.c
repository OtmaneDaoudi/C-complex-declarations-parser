#include "dcl.h"

extern int tokenType; 
extern token lastToken; 

int main(void)
{
    //gettoken test
    int c; 
    while( (c = getchar()) != '\n')
    {
        ungetc(c, stdin); 
        getToken(); 
        if(tokenType == NAME) printf("id : %s\n", lastToken.identifier); 
        else if(tokenType == O_PARAN ||tokenType == C_PARAN || tokenType == O_BRACKET ||tokenType == C_BRACKET) printf("pran/brack\n"); 
        else if(tokenType == NUMBER) printf("nbr : %d\n", lastToken.size); 
        else{ printf("*\n");}
    }
    return 0; 
}