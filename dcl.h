#ifndef DCL_H
#define DCL_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX_TOKEN_SIZE 100
#define MAX_BUFFER_SIZE 200

enum TOKENS{NAME, O_PARAN, C_PARAN, O_BRACKET, C_BRACKET, NUMBER, END};

union token
{
    int size; //size for arrays
    char identifier[MAX_BUFFER_SIZE]; //names of variables
    int other; 
}; 
typedef union token token; 


void dcl(void); 
void dir_dcl(void); 
void getToken(void);

#endif