#include "dcl.h"

extern char token;
extern token_t token_data;  

int main(void)
{
    //gettoken test
    int c; 
    while( (c = getchar()) != '\n')
    {
        ungetc(c, stdin); 
        getToken();
        if(token == '(' || token == ')' || token == ']' || token == '[') printf("paran / brack\n"); 
        else if(token == '*') printf("star\n");
        else if(token == NAME) printf("id = %c\n", token_data.identifier); 
        else {printf("size = %d\n", token_data.size); }

    }
    return 0; 
}