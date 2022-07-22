#include "eval.h"

#include "tokens.h"
#include "utils/bin_tree.h"

#include "../my_math/my_math.h"

double eval(struct tree *ast)
{
    double res = 0;
    struct token *tok = ast->key;
    if(tok->kind==Number)
        res = tok->value;
    else
    {
        if(tok->value=='-')
        {
            res = -eval(ast->right);
            if(ast->left!=NULL)
                res += eval(ast->left);
        }
        else if(tok->value=='+')
        {
            res = eval(ast->right);
            if(ast->left!=NULL)
                res += eval(ast->left);
        }
        else if(tok->value=='*')
            res = eval(ast->left)*eval(ast->right);
        else if(tok->value=='/')
            res = eval(ast->left)/eval(ast->right);
        else // if(is_pow(token))
            res = my_pow(eval(ast->right), eval(ast->left));

        ast->right = NULL;
        ast->left = NULL;
    }

    tree_free(ast, &token_free);
    return res;
}
