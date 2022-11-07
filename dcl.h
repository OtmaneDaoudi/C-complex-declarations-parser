#ifndef DCL_H
#define DCL_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX_TOKEN_SIZE 100
#define MAX_BUFFER_SIZE 200

enum TOKENS{NAME, NUMBER};

union token_t
{
    int size; //size for arrays
    char identifier; //names of variables
}; 
typedef union token_t token_t; 

void dcl(void); 
void A(void);
void dirdcl(void);
void dirdcl1(void); 
void dirdcl2(void); 

void getToken(void); //fetch next token from stdin

#endif