#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

t_btree *bstree_create_node(int item) {
    t_btree *res = malloc(sizeof(t_btree));
    res->number = item;
    res->left = NULL;
    res->right = NULL;
    return res;
}
int compare(int a, int b) { return a - b; }
void output(int data) { printf("%d ", data); }
void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    int res = cmpf(root->number, item);
    if (res > 0) {
        if (root->left != NULL) {
            bstree_insert(root->left, item, compare);
        } else
            root->left = bstree_create_node(item);
    } else if (res < 0) {
        if (root->right != NULL) {
            bstree_insert(root->right, item, compare);
        } else
            root->right = bstree_create_node(item);
    }
}
void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    bstree_apply_infix(root->left, output);
    applyf(root->number);
    bstree_apply_infix(root->right, output);
}
void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    applyf(root->number);
    bstree_apply_prefix(root->left, output);
    bstree_apply_prefix(root->right, output);
}
void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    bstree_apply_postfix(root->right, output);
    applyf(root->number);
    bstree_apply_postfix(root->left, output);
}
void destroy(t_btree *root) {
    if (root == NULL) {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    free(root);
}
