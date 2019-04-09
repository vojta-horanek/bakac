#ifndef COMMANDS_H
#define COMMANDS_H

#include "parser.h"
#include "user.h"

#define nextWord()\
    while (arg[word] != ' ' && arg[word++] != '\0');\
    word++;

typedef struct 
{
    char* str;
    void (*function)(char *, size_t);

} COMMAND;

void show(char *arg, size_t word);
void save(char *arg, size_t word);
void _remove(char *arg, size_t word);
void help(char *arg, size_t word);

#endif
