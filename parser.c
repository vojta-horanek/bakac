#include "parser.h"

#define NUM_COMMANDS 4

COMMAND commands[NUM_COMMANDS] =
{
    {"show", show},
    {"save", save},
    {"remove", _remove},
    {"?", help}
};

const char *errors[] =
{
    "Unrecognized command",
    "Incomplete command",
    "Cannot remove `startup-config`"
};

int parse()
{

    printf("\033[0;32m%s>\033[0m ", user->username);

    char c = 1;
    size_t allocated = 0;
    size_t len = 0;
    char *input;

    /*allocate initial buffer*/
    input = malloc(10 * sizeof(char));
    if (!input)
        return 1;
    allocated = 10;
    while (c != '\n')
    {
        c = (char)getchar();
        /*epand buffer if allocated == len*/
        if (len >= allocated)
        {
            allocated *= 2;
            remem(allocated);
        }
        input[len++] = c;
    }
    /*add leading null*/
    input[--len] = '\0';

    size_t word = 0;
    /*detect first space*/
    while (input[word] != ' ' && input[word++] != '\0');
    
    /*find the command and then execute it with the function pointer*/
    int foundCommand = 0;
    for(int i = 0; i < NUM_COMMANDS; i++)
    {
        if (strncmp(input, commands[i].str, word) == 0)
        {
            commands[i].function(input, word);
            foundCommand = 1;
            break;
        }
    }
    
    /*special cases that the are handeled by the shell*/
    if (!foundCommand)
    {
        if (strncmp(input, "exit", word) == 0)
        {
            free(input);
            return 0;
        }
        else if (strcmp(input, "") == 0);
        else
        {
            shellError(UNRECOGNIZED);
        }
    }

    free(input);

    return 1;
}

void shellError(SE err)
{
    unsigned char message = 0;
    switch(err)
    {
        case INCOMPLETE:
            message = 1;
            break;
        case FILE_DEL:
            message = 2;
            break;
        default:
        case UNRECOGNIZED:
            message = 0;
            break;
    }

    printf("%% %s\n", errors[message]);

}
