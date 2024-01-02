#include <stdio.h>
#include "trees/bst.h"
#include "trees/avl.h"


int main() {
    AVLTree tree = AVLCreate();

    // Árvore A
    printf("\nARVORE A\n\n");
    tree = AVLCreate();
    AVLInsertOrdered(&tree, 12);
    AVLInsertOrdered(&tree, 8);
    AVLInsertOrdered(&tree, 20);
    AVLInsertOrdered(&tree, 4);
    AVLInsertOrdered(&tree, 10);
    AVLInsertOrdered(&tree, 18);
    AVLInsertOrdered(&tree, 26);
    AVLInsertOrdered(&tree, 2);
    AVLInsertOrdered(&tree, 6);
    AVLInsertOrdered(&tree, 9);
    AVLInsertOrdered(&tree, 11);
    AVLInsertOrdered(&tree, 14);
    AVLInsertOrdered(&tree, 19);
    AVLInsertOrdered(&tree, 22);
    AVLInsertOrdered(&tree, 28);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    // Árvore B
    printf("ARVORE B\n\n");
    tree = AVLCreate();
    AVLInsertOrdered(&tree, 12);
    AVLInsertOrdered(&tree, 8);
    AVLInsertOrdered(&tree, 20);
    AVLInsertOrdered(&tree, 4);
    AVLInsertOrdered(&tree, 10);
    AVLInsertOrdered(&tree, 18);
    AVLInsertOrdered(&tree, 26);
    AVLInsertOrdered(&tree, 2);
    AVLInsertOrdered(&tree, 6);
    AVLInsertOrdered(&tree, 9);
    AVLInsertOrdered(&tree, 14);
    AVLInsertOrdered(&tree, 19);
    AVLInsertOrdered(&tree, 22);
    AVLInsertOrdered(&tree, 28);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    // Árvore C
    tree = AVLCreate();
    printf("ARVORE C\n\n");
    AVLInsertOrdered(&tree, 12);
    AVLInsertOrdered(&tree, 8);
    AVLInsertOrdered(&tree, 20);
    AVLInsertOrdered(&tree, 4);
    AVLInsertOrdered(&tree, 10);
    AVLInsertOrdered(&tree, 18);
    AVLInsertOrdered(&tree, 2);
    AVLInsertOrdered(&tree, 6);
    AVLInsertOrdered(&tree, 11);
    AVLInsertOrdered(&tree, 14);
    AVLInsertOrdered(&tree, 19);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    // Árvore D
    printf("ARVORE D:\n\n");
    tree = AVLCreate();
    AVLInsertOrdered(&tree, 12);
    AVLInsertOrdered(&tree, 20);
    AVLInsertOrdered(&tree, 18);
    AVLInsertOrdered(&tree, 14);
    AVLInsertOrdered(&tree, 19);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    return 0;
}
