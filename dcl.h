#ifndef DCL_H
#define DCL_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

enum TOKENS{NAME, NUMBER, END};

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

void parseDataType(void); 
void syntaxError(const char *); 
void getToken(void); //fetch next token from stdin
#endif