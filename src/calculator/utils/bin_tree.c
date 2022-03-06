#include "bin_tree.h"
#include <stdlib.h>
#include <string.h>

struct tree* tree_new(void *data, size_t data_size,
                                            void *left, void *right)
{
    if(data==NULL || data_size==0)
        return NULL;

    struct tree *new = malloc(sizeof(struct tree));

    new->key = malloc(data_size);
    memcpy(new->key, data, data_size);
    new->left = left;
    new->right = right;

    return new;
}

void tree_insert_left(struct tree *t, void *insert,
                                                            size_t data_size)
{
    if(t->left==NULL && insert!=NULL && data_size!=0)
        t->left = tree_new(insert, data_size, NULL, NULL);
}

void tree_insert_right(struct tree *t, void *insert,
                                                            size_t data_size)
{
    if(t->right==NULL && insert!=NULL && data_size!=0)
        t->right = tree_new(insert, data_size, NULL, NULL);
}

int bin_tree_height(struct tree *t)
{
    if(t==NULL)
        return -1;

    int right_height = bin_tree_height(t->right);
    int left_height = bin_tree_height(t->left);

    if(right_height>left_height)
        return 1 + right_height;

    return 1 + left_height;
}

size_t tree_size(struct tree *t)
{
    if(t==NULL)
        return 0;

    return 1 + tree_size(t->left) + tree_size(t->right);
}

void tree_depth(struct tree *t)
{
    // Replace the print by the behavior you want
    // Prefix visit

    if(t->left!=NULL)
        tree_depth(t->left);

    // Infix visit

    if(t->right!=NULL)
        tree_depth(t->right);

    // Sufffix visit
}

void tree_free(struct tree *t, void (*free_function)(void *))
{
    if(t!=NULL)
    {
        tree_free(t->left, free_function);
        tree_free(t->right, free_function);
        free_function(t->key);
        free(t);
    }

}
