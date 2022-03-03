#include "lexer.h"
#include "tokens.h"
#include "utils/vector.h"
#include "utils/vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>

struct vector *lex(char *str)
{
    struct vector *v = vector_new();
    struct token t;
    size_t size = sizeof(struct token);

    while(*str!='\0')
    {
        if(*str>='0' && *str<='9')
        {
            t.kind=Number;
            t.value = strtod(str, &str);
        }
        else
        {
            if(*str=='(' || *str==')')
            {
                t.kind=Separator;
                t.value = *str;
            }
            else if(*str== '-' || *str=='+' || *str=='*' || *str=='/')
            {
                t.kind=Operator;
                t.value = *str;
            }
            else
                errx(1, "Unexpected character '%c' found", *str);
            str++;
        }
        vector_push(v, &t, size);
    }

    return v;
}
