#include "tokens.h"
#include <stdlib.h>

struct token *token_new(char *str, enum kinds kind)
{
    struct token *tok = malloc(sizeof(struct token));

    tok->kind = kind;

    if(kind==Number)
        tok->value = atof(str);
    else
        tok->value = *str;

    return tok;
}

int is_mul_div(struct token *t)
{
    return t->kind==Operator && (t->value=='*' || t->value=='/');
}

int is_add_min(struct token *t)
{
    return t->kind==Operator && (t->value=='-' || t->value=='+');
}
