#include "login.h"

loginRes *get_login_info(xmlDoc *doc)
{
    loginRes *result = malloc(sizeof(*result));
	xmlChar *content = NULL;
	
	for (xmlNode *cur_node = xmlDocGetRootElement(doc); cur_node;
            cur_node = cur_node->next ? cur_node->next : 
            (cur_node == cur_node->last ? NULL : cur_node->children)) {
		
		if (cur_node->type == XML_ELEMENT_NODE) {

            content = xmlNodeGetContent(cur_node);
            
            if (xmlStrEqual(cur_node->name, (const xmlChar*)"res"))
            {
                if(xmlStrEqual(content, (const xmlChar*)"02"))
                {
                    result->res = 2;
                    return result;
                }
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"typ"))
            {
                result->typ = content;
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"ikod"))
            {
                result->ikod = content;
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"salt"))
            {
                result->salt = content;
            }
            else
            {
                xmlFree(content);
            }
        }
	}
	
	return result;
}

char *get_login_token(char *username, char *password)
{
    sprintf(buffer, "%s?gethx=%s", base_url, username);

    string login;
    init_string(&login);

    curl_easy_setopt(curl, CURLOPT_URL, buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &login);

    if(curl_easy_perform(curl) != CURLE_OK) {
        printf("error(get_login_token): curl_easy_perform() failed!\n");
        return NULL;
    }

    xmlDoc *doc = xmlParseMemory(login.ptr, login.len);
	
	freeStr(login);

    if (doc == NULL) {
        printf("error(get_login_token): could not parse the resulting xml\n");
        return NULL;
    }

    loginRes *result = get_login_info(doc);
    xmlFreeDoc(doc);

    if (result->res == 2)
    {
        printf("error: login incorrect (username)\n");
        memset(password, 0, strlen(password));
        free(password);
        return NULL;
    }

    char sha512[SHA512_DIGEST_LENGTH];
    char *hashed;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    size_t out_len = 0;

    /*copy the result from login page to the format we want to hash*/
    sprintf(buffer, "%s%s%s%s", result->salt, result->ikod, result->typ, password);
    
    freeLoginRes(result);    
    memset(password, 0, strlen(password));
    free(password);

    /*create a sha512 hash from the buffer*/
    SHA512((unsigned char*)buffer, strlen(buffer), (unsigned char*)sha512);

    /*encode the sha512 hash to base64*/
    hashed = (char*)base64_encode((unsigned char*)sha512,  sizeof(sha512), &out_len);

    /*create a token format from the user info and the encoded hash*/
    sprintf(buffer, "*login*%s*pwd*%s*sgn*ANDR%04d%02d%02d", username, hashed, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    /*hash the token*/
    SHA512((unsigned char*)buffer, strlen(buffer), (unsigned char*)sha512);

    /*encrypt using base64 again*/
	free(hashed);
    hashed = (char*)base64_encode((unsigned char*)sha512,  sizeof(sha512), &out_len);

    /*replace specific characters*/
    strrep(hashed, '\\', '_');
    strrep(hashed, '/', '_');
    strrep(hashed, '+', '-');

    /*now we have the token used for auth in hashed*/
    return hashed;
}
