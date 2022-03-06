#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lexer.h"
#include "parser.h"
#include "eval.h"
#include "tokens.h"
#include "utils/vector.h"

// direct expression
// interactive mode

double find_result(char *str)
{
    struct vector *v = (shunting_yard(lex(str)));
    double res = eval(parser(v));

    vector_free(v, &token_free);

    return res;
}

void interactive_mode()
{

    size_t buffer_size = 256;
    size_t len = 0;
    char buf[buffer_size];

    while(1)
    {
        write(STDOUT_FILENO,
                "Enter an expression or 'exit' to quit\n>>> ", 43);
        len = read(STDIN_FILENO, buf, buffer_size);
        buf[len]='\0';

        if(strncmp(buf, "exit", 4)==0)
            break;

        pid_t pid = fork();
        if(pid==-1)
            errx(1, "Could not fork");
        if(pid==0)
        {
            printf("The result is: %f\n", find_result(buf));
            exit(EXIT_SUCCESS);
        }
        else
        {
            int status;
            wait(&status);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc>2)
        errx(1, "Usage: %s *optional mathematical expression*", argv[0]);

    if(argc==1)
        interactive_mode();
    else
        printf("The result is: %f\n", find_result(argv[1]));

    return 0;
}
