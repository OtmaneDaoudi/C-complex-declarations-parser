#include "dcl.h"

char token;
token_t token_data;  

char datatype[MAX_TOKEN_SIZE];
char varName; 

void dcl(void)
{
    if(token == '*' || token == '(' || token == NAME) //A dirdcl
    {
        A(); 
        dirdcl(); 
    }
    return; 
}

void A(void)
{
    if(token == '*') //*A  else : return = epsilon
    {
        getToken();
        A(); 
        printf(" pointer to"); 
    }
    return; 
}

void dirdcl(void)
{
    if(token == '(') //(dcl)dirdcl'
    {
        getToken(); //consume (
        dcl(); 
        if(token == ')') getToken(); //consume
        else printf("ERROR : synatx error, missing ).\n"); 
        dirdcl1(); 
    }
    else if(token == NAME)
    {
        varName = token_data.identifier; 
        dirdcl1(); 
    }
    return; 
}

void dirdcl1(void)
{
    if(token == '(')
    {
        getToken();
        if(token == ')') dirdcl1(); 
        else printf("ERROR: syntax error, missing ).\n"); 
    }
    else if(token == '[')
    {
        getToken();
        dirdcl2(); 
    }
    return;
}

void dirdcl2(void)
{
    if(token == ']')
    {
        getToken(); 
        dirdcl1();
    }
    else if(token == NUMBER)
    {
        getToken(); 
        if(token == ']')
        {
            dirdcl1(); 
        }
        else printf("ERROR: missing ].\n"); 
    }
    return; 
}

void getToken(void)
{
    //works only with one char identifiers and one-digit sizes
    //can be further obtimized with automatons
    char c;
    c = getchar();
    if(c == '\n')
    {
        printf("end...\n");
        exit(EXIT_SUCCESS); //end of input 
    } 
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
