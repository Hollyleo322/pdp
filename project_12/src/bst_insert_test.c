#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {
    int a = 7;
    int b = 3;
    t_btree *root = bstree_create_node(a);
    bstree_insert(root, b, compare);
    printf("%s\n", root->left != NULL ? "Place is left SUCCESS" : "Place is right FAIL");
    int c = 10;
    int d = 20;
    t_btree *root_2 = bstree_create_node(c);
    bstree_insert(root_2, d, compare);
    printf("%s\n", root_2->right != NULL ? "Place is right SUCCESS" : "Place is left FAIL");
    destroy(root);
    destroy(root_2);
    return 0;
}