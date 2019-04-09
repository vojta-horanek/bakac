#include "commands.h"

void show(char *arg, size_t word)
{
    nextWord();
    if (strcmp(arg+word, "user") == 0)
        printUser();
    else if (strcmp(arg+word, "token") == 0)
        printf("%s\n", token);
    else
        shellError(INCOMPLETE);
}

void save(char *arg, size_t word)
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

void _remove(char *arg, size_t word)
{
    if(remove("startup-config")) {
        shellError(FILE_DEL);
    }
}

void help(char *arg, size_t word)
{
    nextWord();
    if (strcmp(arg+word, "show") == 0)
    {
        printf(
                "user\tdisplay information about the current user\n"
                "token\tdisplay the current token used for authentication\n"
              );
    }
    else
    {
        printf(
                "show\tdisplay different information (see `? show` for more)\n"
                "exit\texit console\n"
                "save\tsave the current hash and username to `startup-config`\n"
                "remove\tremove `startup-config`\n"
                "?\tdisplay help\n"
              );
    }
}
