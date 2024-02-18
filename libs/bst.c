// Árvore Binária de Pesquisa - Binary Search Tree (BST)

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


BSTNode* BSTNewNode(bstdata_t data) {
    BSTNode* new_node = (BSTNode*) malloc(sizeof(BSTNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

BinarySearchTree BSTCreate() {
    return (BinarySearchTree) { NULL };
}

BinarySearchTree BSTFromNode(BSTNode* root) {
    return (BinarySearchTree) { root };
}

bool BSTIsEmpty(BinarySearchTree tree) {
    return !tree.root;
}

BSTNode* BSTInsert(BinarySearchTree* tree, bstdata_t data) {
    if (BSTIsEmpty(*tree)) {
        tree->root = BSTNewNode(data);
        return tree->root;
    }

    BSTNode* current_node = tree->root;

    for (;;) {
        if (BSTIsLower(data, current_node->data)) {
            if (!current_node->left) {
                current_node->left = BSTNewNode(data);
                return current_node->left;
            }

            current_node = current_node->left;
        } else if (BSTIsGreater(data, current_node->data)) {
            if (!current_node->right) {
                current_node->right = BSTNewNode(data);
                return current_node->right;
            }

            current_node = current_node->right;
        } else {
            // Valor repetido. Não inserir.
            return NULL;
        }
    }
}

BSTNode* BSTSearch(BinarySearchTree tree, bstdata_t data) {
    BSTNode* current_node = tree.root;

    while (current_node) {
        if (BSTIsLower(data, current_node->data)) {
            current_node = current_node->left;
        } else if (BSTIsGreater(data, current_node->data)) {
            current_node = current_node->right;
        } else {
            return current_node;
        }
    }

    return NULL;
}

// Função recursiva interna para BSTForEach()
// Não exposta no header
int _BSTForEach(BSTNode* node, enum BSTTraversal traversal, enum BSTSide order, int (*operation)(BSTNode* node)) {
    if (!node) {
        return 0;
    }

    BSTNode* first_child;
    BSTNode* second_child;

    switch (order) {
        case BST_LEFT: {
            first_child = node->left;
            second_child = node->right;
            break;
        }

        case BST_RIGHT: {
            first_child = node->right;
            second_child = node->left;
            break;
        }
    }

    if (traversal == BST_TRAVERSAL_PRE)
        if (operation(node))
            return 1;

    if (_BSTForEach(first_child, traversal, order, operation))
        return 1;

    if (traversal == BST_TRAVERSAL_IN)
        if (operation(node))
            return 1;

    if (_BSTForEach(second_child, traversal, order, operation))
        return 1;

    if (traversal == BST_TRAVERSAL_POST)
        if (operation(node))
            return 1;
    
    return 0;
}

int BSTForEach(BinarySearchTree tree, enum BSTTraversal traversal, enum BSTSide order, int (*operation)(BSTNode* node)) {
    return _BSTForEach(tree.root, traversal, order, operation);
}

// Função interna recursiva para BSTCount
// Não exposta no header
int _BSTCount(BSTNode* node) {
    if (node) {
        return 1 + _BSTCount(node->left) + _BSTCount(node->right);
    } else {
        return 0;
    }
}

int BSTCount(BinarySearchTree tree) {
    _BSTCount(tree.root);
}

int BSTNodeHeight(BSTNode* node) {
    if (!node) {
        return 0;
    }

    int lheight = BSTNodeHeight(node->left);
    int rheight = BSTNodeHeight(node->right);

    if (lheight > rheight) {
        return 1 + lheight;
    } else {
        return 1 + rheight;
    }
}

// Função interna recursiva para BSTTreeBalanceFactor()
// Não exposta no header
int _BSTTreeBalanceFactor(BSTNode* node) {
    if (!node) {
        return 0;
    }

    int selfbalance = abs(BSTNodeBalanceFactor(node));
    int lbalance = _BSTTreeBalanceFactor(node->left);
    int rbalance = _BSTTreeBalanceFactor(node->right);

    int higher;

    if (lbalance > rbalance)
        higher = lbalance;
    else
        higher = rbalance;

    if (selfbalance > higher) {
        return selfbalance;
    } else {
        return higher;
    }
}

int BSTTreeBalanceFactor(BinarySearchTree tree) {
    return _BSTTreeBalanceFactor(tree.root);
}

int BSTNodeBalanceFactor(BSTNode* node) {
    int lheight = BSTNodeHeight(node->left);
    int rheight = BSTNodeHeight(node->right);
    return lheight - rheight;
}

// Função interna para BSTPrintList()
// Não exposta no header
int _BSTPrintList_print(BSTNode* node) {
    printf("%d ", node->data);
    return 0;
}

void BSTPrintList(BinarySearchTree tree, enum BSTTraversal traversal, enum BSTSide order) {
    printf("[ ");
    _BSTForEach(tree.root, traversal, order, _BSTPrintList_print);
    printf("]\n");
}

// Função interna recursiva para BSTDraw()
// Não exposta no header
void _BSTDraw(BSTNode* node, unsigned int level) {
    if (node) {
        for (int x = 1; x < level; x++) {
            printf("|  ");
        }

        printf("+- %d \n", node->data);

        if (node->left) 
            _BSTDraw(node->left, level + 1);

        if (node->right)
            _BSTDraw(node->right, level + 1);
    }
}

void BSTDraw(BinarySearchTree tree) {
    _BSTDraw(tree.root, 1);
}

int BSTRemove(BinarySearchTree* tree, bstdata_t data) {
    if (BSTIsEmpty(*tree)) {
        return 0;
    }

    int found = 0;
    enum BSTSide last_side;
    BSTNode* current_node = tree->root;
    BSTNode* parent_node = NULL;

    while (current_node) {
        if (BSTIsLower(data, current_node->data)) {
            parent_node = current_node;
            current_node = current_node->left;
            last_side = BST_LEFT;
        } else if (BSTIsGreater(data, current_node->data)) {
            parent_node = current_node;
            current_node = current_node->right;
            last_side = BST_RIGHT;
        } else {
            found = 1;
            break;
        }
    }

    if (!found) {
        return 0;
    }

    BSTNode* substitution;

    if (current_node->left) {
        if (current_node->right) {  
            /* O nodo a ser removido tem dois filhos */

            // Substituir o nodo atual pelo menor nodo da subárvore direita

            BSTNode* smallest_node = current_node->right;

            if (!smallest_node->left) {
                // O menor nodo da subárvore direita é o filho direito do nodo atual
                
                smallest_node->right = current_node->right;
            } else {
                BSTNode* smallest_node_parent = current_node;
                
                while (smallest_node->left) {
                    smallest_node_parent = smallest_node;
                    smallest_node = smallest_node->left;
                }

                smallest_node_parent->left = smallest_node->right;
            }

            substitution = smallest_node;
            smallest_node->left = current_node->left;
        } else {                      
            /* O nodo a ser removido tem spenas filho esquerdo */
            substitution = current_node->left;
        }
    } else if (current_node->right) {
        /* O nodo a ser removido tem apenas filho direito */
        substitution = current_node->right;
    } else {                          
        /* O nodo a ser removido é nodo folha */
        // (Nodo raiz && Nodo folha) => A árvore só tem um nodo
        substitution = NULL;
    }

    if (!parent_node) {
        tree->root = substitution;
    } else {
        switch (last_side) {
            case BST_LEFT: {
                parent_node->left = substitution;
                break;
            }

            case BST_RIGHT: {
                parent_node->right = substitution;
                break;
            }
        }
    }

    free(current_node);
    return 1;
}

// Função interna para BSTEmpty()
// Não exposta no header
int _BSTEmpty_free(BSTNode* node) {
    free(node);
    return 0;
}

void BSTEmpty(BinarySearchTree* tree) {
    BSTForEach(*tree, BST_TRAVERSAL_POST, BST_LEFT, _BSTEmpty_free);
    tree->root = NULL;
}


/*
 * Até aqui, neste arquivo, a árvore era agnóstica do tipo concreto de `avldata_t`.
 * A partir daqui, as funções são específicas para o tipo concreto `Food`.
 */

bool BSTIsEqual(Food a, Food b) {
    return FoodIsEqual(a, b);
}

bool BSTIsGreater(Food a, Food b) {
    return FoodIsGreater(a, b);
}

bool BSTIsLower(Food a, Food b) {
    return FoodIsLower(a, b);
}

void BSTFreeNode(BSTNode* node) {
    free(node->data.name);
    free(node);
}
