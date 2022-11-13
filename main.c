#include "dcl.h"

extern char token;
extern token_t token_data;  
extern char datatype[MAX_TOKEN_SIZE]; 
extern char varname; 
extern char * ouput[]; 
extern int output_size; 

int main(void)
{
    getToken();
    dcl(); 
    printf("done\n");
    printf("%c : ", varname);
    for(int i=0; i<output_size; i++) printf("%s", ouput[i]); 
    printf("\nend of prog\n"); 
    return 0; 
}