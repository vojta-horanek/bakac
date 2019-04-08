#ifndef MSTRING_H
#define MSTRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define freeStr(x)\
	free((x).ptr);

typedef struct string {

    char *ptr;
    size_t len;

} string;

void strrep(char *string, char old, char new);
void init_string(string *s);
size_t curl_str_write(void *ptr, size_t size, size_t nmemb, string *s);

#endif
