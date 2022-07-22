#ifndef TOKENS_H
#define TOKENS_H

enum kinds
{
    Number,
    Operator, // +, -, /, *, ^
    Separator, // '(' and ')'
};

struct token
{
    enum kinds kind;
    double value;
};

struct token *token_new(char *str, enum kinds kind);

void token_free(void *t);

int is_pow(struct token *t);

int is_mul_div(struct token *t);

int is_add_min(struct token *t);

// Return true if token2 has greater precedence
int has_greater_precedence(struct token *token1, struct token *token2);

int has_equal_precedence(struct token *token1, struct token *token2);
#endif /* ! TOKENS_H */
