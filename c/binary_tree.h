#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>

typedef int nodetype;
/**
 * @brief Struct of tree's node.
 * @details This structure implements tree's node. It contains pointers to the right
 * and left nodes and the value. Type of value can be changed by changing nodetype.
 */
struct _binary_tree_node {
    struct _binary_tree_node *left; /*!< Pointer to the left element. */
    struct _binary_tree_node *right; /*!< Pointer to the right element. */
    nodetype val; /*!< Value that node contains. */
};
typedef struct _binary_tree_node btree_node;

typedef int (*comparator)(const nodetype, const nodetype); //callback для сравнения двух элементов дерева
typedef void (*executor)(btree_node, void *data); //callback, вызывающаяся для каждого элемента дерева
/** @brief Struct of tree.
 * @details This structure implements tree. It contains pointers to the
 * root; comparator function count of elements in a tree.
 */
struct _binary_tree {
    btree_node *root;
    comparator cmp;
    size_t size;
};

typedef struct _binary_tree btree;

/**
 * Операции над деревом
 */

btree_node *bnode_create(const nodetype);
void bnode_delete(btree_node*);

btree *btree_create(comparator);
void btree_delete(btree*);

void btree_insert(btree*, const nodetype);
void btree_symmetric_pass(const btree*, executor, void*);

void btree_beatiful_print(const btree*);

#endif // BINARY_TREE_H



