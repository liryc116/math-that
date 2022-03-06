#include "lexer.h"

#include "tokens.h"
#include "utils/vector.h"

#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <ctype.h>

int is_operator(char c)
{
    return c=='+' || c=='-' || c=='/' || c=='*';
}

struct vector *lex(char *str)
{
    struct vector *v = vector_new();
    struct token t;
    t.kind = Operator;
    int sep_count = 0;
    size_t size = sizeof(struct token);

    for(; isspace(*str); str++);
    while(*str!='\0')
    {
        if(*str>='0' && *str<='9')
        {
            if(t.kind == Number)
                errx(1, "Two numbers following");
            t.kind=Number;
            t.value = strtod(str, &str);
        }
        else
        {
            if(*str=='(' || *str==')')
            {
                if(*str=='(')
                    sep_count++;
                else
                    sep_count--;
                t.kind=Separator;
                t.value = *str;
            }
            else if(is_operator(*str))
            {
                t.kind=Operator;
                t.value = *str;
            }
            else
                errx(1, "Unexpected character '%c' found", *str);
            str++;
        }
        vector_push(v, &t, size);
        for(; isspace(*str); str++);
    }

    if(sep_count!=0)
        errx(1, "Unopend/unclosed parenthesis");

    return v;
}
