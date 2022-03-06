#include "lexer.h"

#include "tokens.h"
#include "utils/vector.h"

#include <stddef.h>
#include <stdlib.h>
#include <err.h>

int is_operator(char c)
{
    return c=='+' || c=='-' || c=='/' || c=='*';
}

int is_space(char c)
{
    return c==' ' || c=='\f' || c=='\n' || c=='\r' || c=='\t' || c=='\v';
}

int accept_bin_op(struct token *t)
{
    return t->kind==Number || t->value==')';
}

void two_num(struct token *t)
{
    if(t->kind == Number)
        errx(1, "Two numbers following");
}

void two_bin_op(struct token *t, char c)
{
    if(is_mul_div(t) && (c=='*' || c=='/'))
        errx(1, "Two binary operators following");
}

void op_sep(struct token *t)
{
    if(t->kind==Operator)
        errx(1, "Operator before ')'");
}

struct vector *lex(char *str)
{
    struct vector *v = vector_new();
    struct token t;
    t.kind = Operator;
    int sep_count = 0;
    size_t size = sizeof(struct token);

    for(; is_space(*str); str++);
    while(*str!='\0')
    {
        if(*str>='0' && *str<='9')
        {
            two_num(&t);
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
                {
                    op_sep(&t);
                    sep_count--;
                }
                t.kind=Separator;
                t.value = *str;
            }
            else if(is_operator(*str))
            {
                two_bin_op(&t, *str);
                t.kind=Operator;
                t.value = *str;
            }
            else
                errx(1, "Unexpected character '%c' found", *str);
            str++;
        }
        vector_push(v, &t, size);
        for(; is_space(*str); str++);
    }

    if(sep_count!=0)
        errx(1, "Unopend/unclosed parenthesis");

    return v;
}
