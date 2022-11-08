#include "dcl.h"

char token;
token_t token_data;  

char datatype[MAX_TOKEN_SIZE];
char varName; 

void dcl(void)
{
    printf("dcl\n");
    if(token == '*' || token == '(' || token == NAME) //A dirdcl
    {
        A(); 
        dirdcl(); 
    }
    return; 
}

void A(void)
{
    printf("A\n"); 
    if(token == '*') //*A  else : return = epsilon
    {
        getToken();
        A(); 
        printf(" pointer to\n"); 
    }
    return; 
}

void dirdcl(void)
{
    printf("dirdcl\n"); 
    if(token == '(') //(dcl)dirdcl'
    {
        getToken(); //consume (
        dcl(); 
        if(token == ')') 
        {
            getToken();
            dirdcl1();
        }  
        else printf("ERROR : synatx error, missing )[LAST token = %c].\n", token);  
    }
    else if(token == NAME)
    {
        varName = token_data.identifier; 
        getToken(); 
        dirdcl1(); 
    }
    return; 
}

void dirdcl1(void)
{
    printf("dirdcl1\n"); 
    if(token == '(')
    {
        getToken();
        if(token == ')') dirdcl1(); 
        else printf("ERROR: syntax error, missing ) [last token = %c].\n", token); 
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
    printf("dirdcl2\n"); 
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
        else printf("ERROR: missing ].[last token %c]\n", token); 
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
