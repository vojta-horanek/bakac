#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "commands.h"

#define strycmp(x,y)\
    (strcmp(x,y) == 0)

#define remem(size)\
    char *temp = realloc(input, (size)*sizeof(char));\
    if (!temp)\
    {\
        free(input);\
        return 1;\
    }\
    input = temp;


typedef enum {
    
    INCOMPLETE,
    UNRECOGNIZED,
    FILE_DEL

} SE;


extern USER *user;
extern char *token;

int parse();
void shellError(SE err);

#endif
