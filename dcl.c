#include "dcl.h"

char token = 0;
token_t token_data;  

char * ouput[20];
int output_size = 0; 
  
char varname; 

void dcl(void)
{
    if(token == '*' || token == '(' || token == NAME)
    {
        A(); 
        dirdcl(); 

        if(output_size > 1)
        {
            int last = output_size-1; 
            if(strcmp(ouput[last-1], "pointer to ") == 0)
            {
                //swap and merge last two elements
                ouput[last] = realloc(ouput[last], strlen(ouput[last]) + 13); 
                strcat(ouput[last], "pointer to ");
                free(ouput[last-1]); 
                ouput[last-1] = ouput[last];  
                output_size--; 
                // printf("swap & merge at dcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n"); 
            }
            else{
                //merge last tow elements
                ouput[last-1] = realloc(ouput[last - 1], strlen(ouput[last - 1]) + 1 + strlen(ouput[last]) + 1); 
                strcat(ouput[last - 1], ouput[last]);
                free(ouput[last]); 
                output_size--;
                // printf("merge at dcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n"); 
            }
        }
    }
    else if(token == '(') return; 
    else syntaxError(NULL); 
}

void A(void)
{
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
    else syntaxError(NULL); 
}

void dirdcl(void)
{
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
                int last = output_size - 1; 
                ouput[last - 1] = realloc(ouput[last - 1], strlen(ouput[last - 1]) + 1 + strlen(ouput[last]) + 1); 
                strcat(ouput[last - 1], ouput[last]);
                free(ouput[last]);
                output_size--; 
                // printf("merge at dirdcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n"); 
            }
        }  
        else syntaxError("missing ).");  
    }
    else if(token == NAME)
    {
        varname = token_data.identifier; 

        getToken(); 
        dirdcl1(); 
        // printf("no merge at dirdcl : "); for(int i=0; i<output_size; i++) printf("%s", ouput[i]); printf("\n");
    }
    else syntaxError(NULL); 
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
        else syntaxError("missing )."); 
    }
    else if(token == ')' || token == END) return; 
    else if(token == '[')
    {
        getToken();
        dirdcl2(); 
    }
    else syntaxError(NULL); 
}

void dirdcl2(void)
{
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
        else syntaxError("missing ]."); 
    }
    else syntaxError(NULL);
    return; 
}

void getToken(void)
{
    //works only with one char identifiers and one-digit sizes
    char c = getchar();

    if(token == END) return; 
    else if(c == '\n')
    {
        token = END;
    } 
    else if(c == '(' || c == ')' || c == ']' || c == '[' || c == '*') token = c; //[ ] ( ) *
    else if(isdigit(c)) // NUMBER
    {
        char num[2] = {c, 0};
        token = NUMBER; 
        token_data.size = atoi(num); 
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

char datatype[20];

void parseDataType(void)
{
    int c = getchar(); 
    ungetc(c, stdin); 
    scanf("%s", datatype); 
    // printf("parsed string : %s\n", datatype); 
    if(strcmp(datatype, "char") == 0 || strcmp(datatype, "int") == 0 || strcmp(datatype, "float") == 0 
        || strcmp(datatype, "double") == 0 || strcmp(datatype, "short") == 0 || strcmp(datatype, "void") == 0)
    {
        getchar(); //consume remaining space
        return;
    }
    else {
        printf("Datatype error.\n"); 
        exit(EXIT_FAILURE); 
    }
    
}

void syntaxError(const char * msg)
{
    if(msg == NULL) printf("Syntax error."); 
    else printf("Syntax error: %s\n", msg); 
    exit(EXIT_FAILURE); 
}