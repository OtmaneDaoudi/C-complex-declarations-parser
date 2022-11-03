#include "dcl.h"

int tokenType;
token lastToken;  

char datatype[MAX_TOKEN_SIZE];
// char out[MAX_BUFFER_SIZE]; 

void dcl(void)      
{
    int temp, count = 0; 
    while((temp = getchar()) == '*') count++; 
    ungetc(temp, stdin); 
    dir_dcl(); 
    for(int i=0; i<count; i++) printf("pointer to "); 
}

void dir_dcl(void)
{
    getToken(); 
    if(tokenType == NAME)
    {
        printf("%s is a ", lastToken.identifier);
        dir_dcl(); 
    }
    else if(tokenType == O_PARAN)
    {
        char c = getchar(); //store next token
        if(c == ')') //dir-dcl()
        {
            printf("function returning "); 
            dir_dcl(); 
        }
        else //(dcl)
        {
            ungetc(c, stdin); 
            dcl(); 
        }
    }
    else if(tokenType == O_BRACKET)
    {
        getToken(); 
        if(tokenType == NUMBER)
        {
            int size = lastToken.size; 
            getToken(); 
            if(tokenType == C_BRACKET)
            {
                printf("array of size %d ", size); 
                dir_dcl(); 
            }
            else
            {
                printf("syntax error \n"); 
                exit(EXIT_FAILURE); 
            }
        }
        else if(tokenType == C_BRACKET)
        {
            printf("array of "); 
            dir_dcl(); 
        }
    }
    else 
    {
        printf("syntax error [outer]\n");
        exit(EXIT_FAILURE); 
    } 
}

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