#ifndef USER_H
#define USER_H

#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include "mstring.h"

typedef struct {

    xmlChar *name;
    xmlChar *strtyp;
    xmlChar *skola;
    xmlChar *trida;
    char *username;

} USER;

extern CURL *curl;
extern const char base_url[];
extern char buffer[512];

USER* get_user_info(char *token);

#endif
