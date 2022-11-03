#include "dcl.h"

int tokenType;
token lastToken;  

char datatype[MAX_TOKEN_SIZE];
char out[MAX_BUFFER_SIZE]; 

void getToken(void)
{
    //can be further obtimised with automatons
    //works only with one char identifiers and one-digit sizes
    char c;
    if((c = getchar()) == EOF) return;
    switch(c)
    {
        case '(':
            lastToken.other = tokenType = O_PARAN;
            break;  
        case ')':
            lastToken.other = tokenType = C_PARAN;
            break; 
        case ']':
            lastToken.other = tokenType = C_BRACKET;
            break; 
        case '[':
            lastToken.other = tokenType = O_BRACKET;
            break; 
        case '*':
            tokenType = X; 
            break; 
        default: //name or numbers  
            if(isalpha(c))
            {
                lastToken.identifier[0] = c; 
                lastToken.identifier[1] = 0;
                tokenType = NAME; 
            }
            else if(isdigit(c))
            {
                lastToken.size = atoi(&c); 
                tokenType = NUMBER;
            }
    }
}