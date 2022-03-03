#ifndef TOKENS_H
#define TOKENS_H

enum kinds
{
    Number,
    Operator, // +, -, /, *
    Separator, // '(' and ')'
};

struct token
{
    enum kinds kind;
    double value;
};

struct token *token_new(char *str, enum kinds kind);

int is_mul_div(struct token *t);

int is_add_min(struct token *t);

#endif /* ! TOKENS_H */
