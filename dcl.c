#include "dcl.h"
/*swapping happens at :
    dcl : if preceeded by a "pointer to " then, swap and merge
    dirdcl : 
        merge last two elements
*/ 

char token = 0;
token_t token_data;  

char * ouput[20];
int output_size = 0; 
  
char datatype[MAX_TOKEN_SIZE];
char varname; 

void dcl(void)
{
    // printf("dcl\n");
    if(token == '*' || token == '(' || token == NAME)
    {
        A(); 
        dirdcl(); 
        //output processin checkpoint
        if(output_size > 1)
        {
            int last = output_size-1; 
            if(strcmp(ouput[last-1], "pointer to ") == 0)
            {
                //swap and merge
                //extend last
                ouput[last] = realloc(ouput[last], strlen(ouput[last]) + 13); 
                strcat(ouput[last], " pointer to ");
                //swap
                free(ouput[last-1]); 
                ouput[last-1] = ouput[last]; 
                // free(ouput[last]); 
                // printf("output last : %s\n", ouput[last]); 
                output_size--; 
                printf("swap & merge at dcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n"); 
            }
            else{
                //add last to last-1 and free last
                ouput[last-1] = realloc(ouput[last - 1], strlen(ouput[last - 1]) + 1 + strlen(ouput[last]) + 1); 
                strcat(ouput[last - 1], ouput[last]);
                free(ouput[last]); 
                output_size--;
                printf("merge at dcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n"); 

            }
        }
    }
    else if(token == '(') return; 
    else printf("Syntax error at %c\n", token); 
}

void A(void)
{
    // printf("A\n"); 
    if(token == '*') 
    {
        getToken();
        A(); 
        //push "pointer to " into the output
        ouput[output_size] = (char*)malloc(12); 
        strcpy(ouput[output_size], "pointer to "); 
        output_size++; 
    }
    else if(token == '(' || token == NAME) return; 
    else printf("Syntax error at %c\n", token); 
}

void dirdcl(void)
{
    // printf("dirdcl\n"); 
    if(token == '(') 
    {
        getToken(); 
        dcl(); 
        if(token == ')') 
        {
            getToken();
            dirdcl1();
            // merge last two elements
            if(output_size > 1)
            {
                printf("here\n"); 
                int last = output_size - 1; 
                ouput[last - 1] = realloc(ouput[last - 1], strlen(ouput[last - 1]) + 1 + strlen(ouput[last]) + 1); 
                strcat(ouput[last - 1], ouput[last]);
                free(ouput[last]);
                // ouput[last-1] = ouput[last]; 
                // free(ouput[last]); 
                output_size--; 
                printf("merge at dirdcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n"); 
            }
        }  
        else printf("ERROR : synatx error, missing )[LAST token = %c].\n", token);  
    }
    else if(token == NAME)
    {
        varname = token_data.identifier; 
        // //push "name is a "        
        // ouput[output_size] = (char*)malloc(8); 
        // snprintf(ouput[output_size], 8, "%c is a ", token_data.identifier);
        // output_size++; 

        getToken(); 
        dirdcl1(); 
        printf("no merge at dirdcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n");
    }
    else printf("Syntax error at %c\n", token); 
}

void dirdcl1(void)
{
    // printf("dirdcl1\n"); 
    if(token == '(')
    {
        getToken();
        if(token == ')') 
        {
            //push "function returning " 20
            ouput[output_size] = (char*)malloc(20); 
            strcpy(ouput[output_size], "function returning "); 
            output_size++;

            getToken(); 
            dirdcl1(); 
        }
        else printf("ERROR: syntax error, missing ) [last token = %c].\n", token); 
    }
    else if(token == ')' || token == END) return; 
    else if(token == '[')
    {
        getToken();
        dirdcl2(); 
    }
    else printf("Synatx error at %c\n", token); 
}

void dirdcl2(void)
{
    // printf("dirdcl2\n"); 
    if(token == ']')
    {
        //push "array of "
        ouput[output_size] = (char*)malloc(10); 
        strcpy(ouput[output_size], "array of "); 
        output_size++; 

        getToken(); 
        dirdcl1();
    }
    else if(token == NUMBER)    
    {
        int size = token_data.size; 
        getToken(); 
        if(token == ']')
        {
            //push "array[size] of "
            ouput[output_size] = (char*)malloc(13); 
            snprintf(ouput[output_size], 13, "array[%d] of ", size);
            output_size++; 
            
            getToken(); 
            dirdcl1(); 
        }
        else printf("ERROR: missing ].[last token %c]\n", token); 
    }
    else printf("Synatx error at %c\n", token);
    return; 
}

void getToken(void)
{
    //works only with one char identifiers and one-digit sizes
    //can be further obtimized with automatons
    char c = getchar();

    if(token == END) return; 
    else if(c == '\n')
    {
        token = END;
    } 
    else if(c == '(' || c == ')' || c == ']' || c == '[' || c == '*') token = c; //[ ] ( ) *
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