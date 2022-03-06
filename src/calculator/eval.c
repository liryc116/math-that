#include "eval.h"

#include "tokens.h"
#include "utils/bin_tree.h"

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
        else // tok->value=='/'
            res = eval(ast->left)/eval(ast->right);

        ast->right = NULL;
        ast->left = NULL;
    }

    tree_free(ast, &token_free);
    return res;
}
