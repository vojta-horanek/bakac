#ifndef LOGIN_H
#define LOGIN_H

#include <openssl/sha.h>
#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <time.h>
#include <string.h>
#include "mstring.h"

#define freeLoginRes(r)\
	xmlFree((r)->typ);\
	xmlFree((r)->ikod);\
	xmlFree((r)->salt);

typedef struct {

    char res;
    xmlChar *typ;
    xmlChar *ikod;
    xmlChar *salt;

} loginRes;

extern unsigned char *base64_encode(const unsigned char *src, size_t len,
        size_t *out_len);

extern CURL *curl;
extern const char base_url[];
extern char buffer[512];

loginRes *get_login_info(xmlDoc *doc);
char *get_login_token(char *username, char *password);

#endif
