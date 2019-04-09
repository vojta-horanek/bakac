#include "user.h"

void getUserInfo(char *token)
{
    user = malloc(sizeof(*user));
    sprintf(buffer, "%s?hx=%s&pm=login", base_url, token);

    string web_result;
    init_string(&web_result);

    curl_easy_setopt(curl, CURLOPT_URL, buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &web_result);

    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        printf("error(get_user_info): curl_easy_perform() failed! %s\n", curl_easy_strerror(res));
        user = NULL;
        return;
    }

    xmlDoc *doc = xmlParseMemory(web_result.ptr, web_result.len);

    freeStr(web_result);

    if (doc == NULL) {
        printf("error(get_user_info): could not parse the resulting xml\n");
        user = NULL;
        return;
    }

    for (xmlNode *cur_node = xmlDocGetRootElement(doc); cur_node;
            cur_node = cur_node->next ? cur_node->next : (cur_node == cur_node->last ? NULL : cur_node->children)) {

        if (cur_node->type == XML_ELEMENT_NODE) {

            xmlChar *content = xmlNodeGetContent(cur_node);

            if (xmlStrEqual(cur_node->name, (const xmlChar*)"result"))
            {
                if (xmlStrEqual(content, (const xmlChar*)"-1"))
                {
                    printf("error: login incorrect (password)\n");
                    user = NULL;
                    return;
                }
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"jmeno"))
            {
                user->name = malloc(strlen((char *)content) + 1);
                if (!user->name)
                    user->name = content;
                else {
                    size_t x = 0;
                    while ((char)content[x] != ',' && (char)content[x] != '\0' ) {
                        user->name[x] = (char)content[x];
                        x++;
                    }
                    user->name[x] = '\0';
                }
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"strtyp"))
            {
                user->strtyp = content;
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"skola"))
            {
                user->skola = content;
            }
            else if (xmlStrEqual(cur_node->name, (const xmlChar*)"trida"))
            {
                user->trida = content;
            }
            else
            {
                xmlFree(content);
            }

        }

    }

    xmlFreeDoc(doc);

}

void printUser()
{
    printf("%s\n\t%s\n\t%s\n\t%s\n", user->name, user->skola, user->strtyp, user->trida);
}
