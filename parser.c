#include "parser.h"

int parse()
{
	/*TODO make this properly*/
	char *bakain;
	printf("%s> ", user->username);
	scanf("%ms", &bakain);

	if(strycmp(bakain, "info"))
	    printf("%s\n\t%s\n\t%s\n\t%s\n", user->name, user->skola, user->strtyp, user->trida);
	else if(strycmp(bakain, "save"))
	{
		FILE *fp = fopen("startup-config", "wb");
		if (fp)
		{
			int x = strlen(token) + 1; 
			fwrite(&x, sizeof(int), 1, fp);
			fwrite(token, strlen(token) + 1, 1, fp);
			
			x = strlen(user->username) + 1;
			fwrite(&x, sizeof(int), 1, fp);
			fwrite(user->username, strlen(user->username) + 1, 1, fp);
			
			fclose(fp);
		}
	}
	else if (strycmp(bakain, "exit"))
	{
		free(bakain);
	    return 0;
	}
	else if (strycmp(bakain, "?"))
	{
		printf("info\tshow user info\nexit\texit bakac\nsave\tsave the current hash and username to a file\n?\tdisplay help\n");
	}
	else
	{
		printf("%% Unrecognized command\n");
	}

	free(bakain);
	
	return 1;
}
