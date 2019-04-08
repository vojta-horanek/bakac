#include <unistd.h>

#include "login.h"
#include "user.h"
#include "parser.h"

#define freeUser(user)\
	if ((user)) {\
		if ((user)->name) 	xmlFree((user)->name);\
		if ((user)->strtyp) xmlFree((user)->strtyp);\
		if ((user)->skola) 	xmlFree((user)->skola);\
		if ((user)->trida) 	xmlFree((user)->trida);\
	}

#define easy_cleanup()\
	free(username);\
	free(token);\
	freeUser(user);\
	curl_easy_cleanup(curl);\
	curl_global_cleanup();\
	xmlCleanupParser();
		        
CURL *curl;
USER *user;
char *token;

const char base_url[] = "https://bakalari.uzlabina.cz/login.aspx";
char buffer[512];

int main(void)
{
    LIBXML_TEST_VERSION;

    char *username;
    char *password;
    
    if (curl_global_init(CURL_GLOBAL_DEFAULT))
		return 2;
	curl = curl_easy_init();
	if(!curl)
		return 1;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_str_write);

    
	FILE *fp = fopen("startup-config", "rb");
	if (fp) 
	{
		/*TODO malloc check*/
		int x = 0;
		
		fread(&x, sizeof(int), 1, fp);
		token = malloc(x*sizeof(char));
		fread(token, x, 1, fp);
		
		fread(&x, sizeof(int), 1, fp);
		username = malloc(x*sizeof(char));
		fread(username, x, 1, fp);
		
		fclose(fp);
	}
	else
	{
	
		printf("Bakalari login: ");
		scanf("%ms", &username);
		password = getpass("Password: ");
		
		token = get_login_token(username, password);
		if (!token) {
			easy_cleanup();
			return 1;
		}
	}
    
	user = get_user_info(token);
    if (user) {
        user->username = username;
	
		while (parse());
	
	}
    easy_cleanup();
	return 0;
}
