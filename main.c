#include "dcl.h"

extern int tokenType; 
extern token lastToken; 

int main(void)
{
    //gettoken test
    int c = getchar(); 
    ungetc(c, stdin); 
    dcl(); 
    return 0; 
}