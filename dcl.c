#include "dcl.h"

char token;
token_t token_data;  

char datatype[MAX_TOKEN_SIZE];
// char out[MAX_BUFFER_SIZE]; 

void dcl(void)
{
    return; 
}

void A(void)
{
    return; 
}

void dirdcl(void)
{
    return; 
}

void dirdcl1(void)
{
    return;
}

void dirdcl2(void)
{

}

void getToken(void)
{
    //works only with one char identifiers and one-digit sizes
    //can be further obtimized with automatons
    char c;
    c = getchar();
    if(c == '(' || c == ')' || c == ']' || c == '[' || c == '*') token = c; //[ ] ( ) *
    else if(isdigit(c)) // NUMBER
    {
        token = NUMBER; 
        token_data.size = atoi(&c); 
    }
    else if(isalpha(c)) // NAME
    {
        token = NAME; 
        token_data.identifier = c; 
    }
    else 
    {
        printf("ERROR : %c is not a valid input\n", c); 
        exit(EXIT_FAILURE); 
    }
}