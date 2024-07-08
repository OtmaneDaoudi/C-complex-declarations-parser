#include "dcl.h"

extern char token;
extern token_t token_data;   
extern char varname; 
extern char * ouput[]; 
extern int output_size; 
extern char datatype[20];

int main(void)
{
    // Example run
    parseDataType(); 
    getToken();
    dcl(); 
    printf("%c : ", varname);
    for(int i=0; i<output_size; i++) printf("%s", ouput[i]); 
    printf("%s.\n", datatype); 
    return 0; 
}