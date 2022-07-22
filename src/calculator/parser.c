#include "parser.h"

#include "tokens.h"
#include "utils/list.h"
#include "utils/bin_tree.h"
#include "utils/vector.h"

#include <err.h>
#include <stdlib.h>
#include <stdio.h>

void stack_to_vect(struct vector *v, struct list *stack, size_t size)
{
        struct token *t = list_pop_front(stack);
        vector_push(v, t, size);
        printf("%c\n", (int)t->value);
        token_free(t);
}

int unload_stack(struct vector *v, struct list *stack)
{
    size_t size = sizeof(struct token);
    while(!list_is_empty(stack) &&
            ((struct token *)stack->next->data)->value!=')')
        stack_to_vect(v, stack, size);
    return list_is_empty(stack);
}

int should_pop(struct token *o1, struct token *o2)
{
    return o2->kind!=Separator &&
        (has_greater_precedence(o1, o2) ||
         (has_equal_precedence(o1, o2) && !is_pow(o1)));
}

struct vector *shunting_yard(struct vector *v)
{
    struct vector *res = vector_new();
    struct list *op_stack = list_new();
    size_t size = sizeof(struct token);

    while(v->size!=0)
    {
        struct token *t = vector_pop(v);
        if(t->kind == Operator)
        {
            while(!list_is_empty(op_stack) &&
                    should_pop(t, op_stack->next->data))
                stack_to_vect(res, op_stack, size);
            list_push_front(op_stack, t, size);
        }
        else if(t->kind == Separator && t->value=='(')
            unload_stack(res, op_stack);
        else if(t->kind == Separator)
            list_push_front(op_stack, t, size);
        else // t->kind == Number
            vector_push(res, t, size);
        token_free(t);
    }

    while(!unload_stack(res, op_stack))
    {
        if(((struct token *)op_stack->next->data)->value==')')
            token_free(list_pop_front(op_stack));
    }
    list_free(op_stack, &token_free);
    vector_free(v, &token_free);

    return res;
}

struct tree *parser(struct vector *v)
{

    struct token *tok = vector_pop(v);

    struct tree *t = tree_new(tok, sizeof(struct token), NULL, NULL);

    if(tok->kind!=Number)
    {
        if(v->size!=0)
        {
            t->right = parser(v);

            if(v->size!=0)
                t->left = parser(v);
        }
    }

    token_free(tok);
    return t;
}
