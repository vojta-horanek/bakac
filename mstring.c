#include "mstring.h"

void strrep(char *string, char old, char new)
{
    for(int i = 0; i < strlen(string); ++i)
    {
        if(string[i] == old) string[i] = new;
    }
}

void init_string(string *s) 
{
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "error(init_string): malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t curl_str_write(void *ptr, size_t size, size_t nmemb, string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "error(curl_str_write): realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;\
}
