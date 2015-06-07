#include <stdio.h>

#include "binary_tree.h"

typedef struct t {
    int s;
    size_t k;
} t;

int compar(const int a, const int b) {
    return a - b;
}

void get_average(btree_node node, void *data) {
    if (node.val % 2 == 0) {
        ((t*)data)->s += node.val;
        ((t*)data)->k++;
    }
}

int main(void)
{
    btree *tree = btree_create(compar);

    int i;
    printf("Enter int elements: ");
    while (!feof(stdin)) {
        int x;
        scanf("%d", &x);
        btree_insert(tree, x);
    }

    t average = {0, 0};

    btree_symmetric_pass(tree, get_average, (void*)&average);
    btree_beatiful_print(tree);

    printf("\nAverage = %f\n", (float)average.s/average.k);

    btree_delete(tree);
    return 0;
}

