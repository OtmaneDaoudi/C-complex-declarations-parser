#include "dcl.h"

extern char token;
extern token_t token_data;  
extern char datatype[MAX_TOKEN_SIZE]; 
extern char varName; 

int main(void)
{
    getToken();
    dcl(); 
    printf("done\n"); 
    return 0; 
}