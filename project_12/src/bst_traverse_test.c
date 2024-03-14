#include <stdio.h>

#include "bst.h"

int main() {
    t_btree *root = NULL;
    int start = 8;
    int array[] = {5, 3, 2, 6, 7, 4, 9};
    root = bstree_create_node(start);
    for (unsigned long i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        bstree_insert(root, array[i], compare);
    }
    bstree_apply_infix(root, output);
    printf("\n");
    bstree_apply_prefix(root, output);
    printf("\n");
    bstree_apply_postfix(root, output);
    destroy(root);
    return 0;
}