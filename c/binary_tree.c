#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

btree_node *bnode_create(const nodetype val) {
    btree_node *node = (btree_node*)malloc(sizeof(btree_node));

    node->left = NULL;
    node->right = NULL;
    node->val = val;

    return node;
}

void bnode_delete(btree_node *node) {
    if (node->left != NULL)
        free(node->left);
    if (node->right != NULL)
        free(node->right);
}

btree *btree_create(comparator compar) {
    btree *tree = (btree*)malloc(sizeof(btree));

    tree->root = NULL;
    tree->cmp = compar;
    tree->size = 0;

    return tree;
}

void btree_delete(btree *tree) {
    bnode_delete(tree->root);
    free(tree->root);
    free(tree);
}

void btree_insert(btree *tree, const nodetype val) {
    if (tree->root == NULL)
        tree->root = bnode_create(val);
    else {
        btree_node *n = tree->root, *p;
        int result;
        while (n) {
            p = n;
            result = tree->cmp(val, n->val);
            if (result > 0) {

                n = p->right;
            }
            else if (result < 0) {

                n = p->left;
            }
            else
                return;
        }
        if (result > 0)
            p->right = bnode_create(val);
        else
            p->left = bnode_create(val);
    }
    tree->size++;
}

void _btree_symmetric_pass(const btree_node *node, executor exec, void *data) {

    if (node) {
        _btree_symmetric_pass(node->left, exec, data);

        (*exec)(*node, data);

        _btree_symmetric_pass(node->right, exec, data);
    }
}

void btree_symmetric_pass(const btree *tree, executor exec, void *data) {
    _btree_symmetric_pass(tree->root, exec, data);
}

void _btree_beatiful_print(const btree_node* node, int level) {
    if (node) {
        _btree_beatiful_print(node->right, level+1);

        int i;
        for (i = 0; i < level; i++)
            printf("     ");
        printf("%d\n", node->val);

        _btree_beatiful_print(node->left, level+1);
    }
}

void btree_beatiful_print(const btree *tree) {
    _btree_beatiful_print(tree->root, 0);
}
