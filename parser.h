#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define strycmp(x,y)\
	(strcmp(x,y) == 0)

extern USER *user;
extern char *token;

int parse();

#endif
