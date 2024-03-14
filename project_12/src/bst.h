#pragma once

typedef struct s_btree {
    struct s_btree *left;
    struct s_btree *right;
    int number;
} t_btree;

t_btree *bstree_create_node(int item);
void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int));
int compare(int a, int b);
void output(int data);
void bstree_apply_infix(t_btree *root, void (*applyf)(int));
void destroy(t_btree *root);
void bstree_apply_infix(t_btree *root, void (*applyf)(int));
void bstree_apply_prefix(t_btree *root, void (*applyf)(int));
void bstree_apply_postfix(t_btree *root, void (*applyf)(int));
