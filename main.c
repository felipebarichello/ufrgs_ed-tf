#include <stdio.h>
#include "trees/bst.h"
#include "trees/avl.h"


int main() {
    AVLTree tree = AVLCreate();

    // Árvore A
    printf("\nARVORE A\n\n");
    tree = AVLCreate();
    AVLInsert(&tree, 12);
    AVLInsert(&tree, 8);
    AVLInsert(&tree, 20);
    AVLInsert(&tree, 4);
    AVLInsert(&tree, 10);
    AVLInsert(&tree, 18);
    AVLInsert(&tree, 26);
    AVLInsert(&tree, 2);
    AVLInsert(&tree, 6);
    AVLInsert(&tree, 9);
    AVLInsert(&tree, 11);
    AVLInsert(&tree, 14);
    AVLInsert(&tree, 19);
    AVLInsert(&tree, 22);
    AVLInsert(&tree, 28);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    // Árvore B
    printf("ARVORE B\n\n");
    tree = AVLCreate();
    AVLInsert(&tree, 12);
    AVLInsert(&tree, 8);
    AVLInsert(&tree, 20);
    AVLInsert(&tree, 4);
    AVLInsert(&tree, 10);
    AVLInsert(&tree, 18);
    AVLInsert(&tree, 26);
    AVLInsert(&tree, 2);
    AVLInsert(&tree, 6);
    AVLInsert(&tree, 9);
    AVLInsert(&tree, 14);
    AVLInsert(&tree, 19);
    AVLInsert(&tree, 22);
    AVLInsert(&tree, 28);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    // Árvore C
    tree = AVLCreate();
    printf("ARVORE C\n\n");
    AVLInsert(&tree, 12);
    AVLInsert(&tree, 8);
    AVLInsert(&tree, 20);
    AVLInsert(&tree, 4);
    AVLInsert(&tree, 10);
    AVLInsert(&tree, 18);
    AVLInsert(&tree, 2);
    AVLInsert(&tree, 6);
    AVLInsert(&tree, 11);
    AVLInsert(&tree, 14);
    AVLInsert(&tree, 19);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    // Árvore D
    printf("ARVORE D:\n\n");
    tree = AVLCreate();
    AVLInsert(&tree, 12);
    AVLInsert(&tree, 20);
    AVLInsert(&tree, 18);
    AVLInsert(&tree, 14);
    AVLInsert(&tree, 19);
    AVLDraw(tree);
    printf("\nFator de balanceamento: %d\n\n\n", AVLBalanceFactor(tree));
    AVLEmpty(&tree);

    return 0;
}
