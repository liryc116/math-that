#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stddef.h>

struct tree {
    struct tree *left, *right;
    void *key;
};

struct tree* tree_new(void *data, size_t data_size,
                                        void *left, void *right);

void tree_insert_left(struct tree *t, void *insert, size_t data_size);

void tree_insert_right(struct tree *t, void *insert, size_t data_size);

int tree_height(struct tree *t);

size_t tree_size(struct tree *t);

void tree_depth(struct tree *t);

void tree_free(struct tree *t, void (*free_function)(void *));

#endif /* ! BIN_TREE_H */
