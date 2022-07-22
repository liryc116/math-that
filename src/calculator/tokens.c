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

void token_free(void *t)
{
    free((struct token *) t);
}

int is_pow(struct token *t)
{
    return t->kind==Operator && t->value=='^';
}

int is_mul_div(struct token *t)
{
    return t->kind==Operator && (t->value=='*' || t->value=='/');
}

int is_add_min(struct token *t)
{
    return t->kind==Operator && (t->value=='-' || t->value=='+');
}

int has_greater_precedence(struct token *token1, struct token *token2)
{
    return (is_pow(token2) && !is_pow(token1)) ||
        (is_mul_div(token2) && is_add_min(token2));
}

int has_equal_precedence(struct token *token1, struct token *token2)
{
    return (is_add_min(token1) && is_add_min(token2)) ||
        (is_mul_div(token1) && is_mul_div(token2)) ||
        (is_pow(token1) && is_pow(token2));
}
