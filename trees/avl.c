// Árvore AVL

#include <stdlib.h>
#include <stdio.h>
#include "avl.h"


AVLNode* AVLNewNode(avldata_t data) {
    AVLNode* new_node = (AVLNode*) malloc(sizeof(AVLNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

AVLTree AVLCreate() {
    return (AVLTree) { NULL };
}

AVLTree AVLFromNode(AVLNode* root) {
    return (AVLTree) { root };
}

avldata_t AVLIsEmpty(AVLTree tree) {
    return !tree.root;
}

// Função interna recursiva para AVLInsert()
// Não exposta no header
// [PENDENTE] Balanceamento
AVLNode* _AVLInsert(AVLNode* node, avldata_t data) {
    if (data < node->data) {
        if (!node->left) {
            AVLNode* new_node = AVLNewNode(data);
            node->left = new_node;
            AVLUpdateHeight(node);
            return new_node;
        }

        AVLNode* ret = _AVLInsert(node->left, data);

        if (ret) {
            AVLUpdateHeight(node);
        }

        return ret;
    } else if (data > node->data) {
        if (!node->right) {
            AVLNode* new_node = AVLNewNode(data);
            node->right = new_node;
            AVLUpdateHeight(node);

            return new_node;
        }

        AVLNode* ret = _AVLInsert(node->right, data);

        if (ret) {
            AVLUpdateHeight(node);
        }

        return ret;
    } else {
        // Valor repetido. Não inserir.
        return NULL;
    }
}

AVLNode* AVLInsert(AVLTree* tree, avldata_t data) {
    if (AVLIsEmpty(*tree)) {
        tree->root = AVLNewNode(data);
        return tree->root;
    }

    return _AVLInsert(tree->root, data);
}

AVLNode* AVLSearch(AVLTree tree, avldata_t data) {
    AVLNode* current_node = tree.root;

    while (current_node) {
        if (data < current_node->data) {
            current_node = current_node->left;
        } else if (data > current_node->data) {
            current_node = current_node->right;
        } else {
            return current_node;
        }
    }

    return NULL;
}

// Função recursiva interna para AVLForEach()
// Não exposta no header
int _AVLForEach(AVLNode* node, enum AVLTraversal traversal, enum AVLSide order, int (*operation)(AVLNode* node)) {
    if (!node) {
        return 0;
    }

    AVLNode* first_child;
    AVLNode* second_child;

    switch (order) {
        case AVL_LEFT: {
            first_child = node->left;
            second_child = node->right;
            break;
        }

        case AVL_RIGHT: {
            first_child = node->right;
            second_child = node->left;
            break;
        }
    }

    if (traversal == AVL_TRAVERSAL_PRE)
        if (operation(node))
            return 1;

    if (_AVLForEach(first_child, traversal, order, operation))
        return 1;

    if (traversal == AVL_TRAVERSAL_IN)
        if (operation(node))
            return 1;

    if (_AVLForEach(second_child, traversal, order, operation))
        return 1;

    if (traversal == AVL_TRAVERSAL_POST)
        if (operation(node))
            return 1;
    
    return 0;
}

int AVLForEach(AVLTree tree, enum AVLTraversal traversal, enum AVLSide order, int (*operation)(AVLNode* node)) {
    return _AVLForEach(tree.root, traversal, order, operation);
}


// Função interna recursiva para BSTCount
// Não exposta no header
int _AVLCount(AVLNode* node) {
    if (node) {
        return 1 + _AVLCount(node->left) + _AVLCount(node->right);
    } else {
        return 0;
    }
}

int AVLCount(AVLTree tree) {
    _AVLCount(tree.root);
}

avlheight_t AVLNodeHeight(AVLNode* node) {
    return node->height;
}

avlheight_t AVLUpdateHeight(AVLNode* node) {
    avlheight_t lheight = node->left  ? AVLNodeHeight(node->left)  : 0;
    avlheight_t rheight = node->right ? AVLNodeHeight(node->right) : 0;

    if (lheight > rheight) {
        node->height = lheight + 1;
    } else {
        node->height = rheight + 1;
    }

    return node->height;
}

// Função interna recursiva para AVLBalanceFactor()
// Não exposta no header
int _AVLBalanceFactor(AVLNode* node) {
    if (!node) {
        return 0;
    }

    int selfbalance = abs(AVLNodeBalanceFactor(node));
    int lbalance = _AVLBalanceFactor(node->left);
    int rbalance = _AVLBalanceFactor(node->right);

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

int AVLBalanceFactor(AVLTree tree) {
    return _AVLBalanceFactor(tree.root);
}

int AVLNodeBalanceFactor(AVLNode* node) {
    int lheight = node->left  ? AVLNodeHeight(node->left)  : 0;
    int rheight = node->right ? AVLNodeHeight(node->right) : 0;
    return lheight - rheight;
}

// Função interna para AVLPrintList()
// Não exposta no header
int _AVLPrintList_print(AVLNode* node) {
    printf("%d ", node->data);
    return 0;
}

void AVLPrintList(AVLTree tree, enum AVLTraversal traversal, enum AVLSide order) {
    printf("[ ");
    _AVLForEach(tree.root, traversal, order, _AVLPrintList_print);
    printf("]\n");
}

// Função interna recursiva para AVLDraw()
// Não exposta no header
void _AVLDraw(AVLNode* node, unsigned int level) {
    if (node) {
        for (int x = 1; x < level; x++) {
            printf("|  ");
        }

        printf("+- %d \n", node->height);

        if (node->left) 
            _AVLDraw(node->left, level + 1);

        if (node->right)
            _AVLDraw(node->right, level + 1);
    }
}

void AVLDraw(AVLTree tree) {
    _AVLDraw(tree.root, 1);
}

// [PENDENTE] Balanceamento
// [PENDENTE] Altura
int AVLRemove(AVLTree* tree, avldata_t data) {
    if (AVLIsEmpty(*tree)) {
        return 0;
    }

    int found = 0;
    enum AVLSide last_side;
    AVLNode* current_node = tree->root;
    AVLNode* parent_node = NULL;

    while (current_node) {
        if (data < current_node->data) {
            parent_node = current_node;
            current_node = current_node->left;
            last_side = AVL_LEFT;
        } else if (data > current_node->data) {
            parent_node = current_node;
            current_node = current_node->right;
            last_side = AVL_RIGHT;
        } else {
            found = 1;
            break;
        }
    }

    if (!found) {
        return 0;
    }

    AVLNode* substitution;

    if (current_node->left) {
        if (current_node->right) {  
            /* O nodo a ser removido tem dois filhos */

            // SuAVLituir o nodo atual pelo menor nodo da subárvore direita

            AVLNode* smallest_node = current_node->right;

            if (!smallest_node->left) {
                // O menor nodo da subárvore direita é o filho direito do nodo atual
                
                smallest_node->right = current_node->right;
            } else {
                AVLNode* smallest_node_parent = current_node;
                
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
            case AVL_LEFT: {
                parent_node->left = substitution;
                break;
            }

            case AVL_RIGHT: {
                parent_node->right = substitution;
                break;
            }
        }
    }

    free(current_node);
    return 1;
}

// Função interna para AVLEmpty()
// Não exposta no header
int _AVLEmpty_free(AVLNode* node) {
    free(node);
    return 0;
}

void AVLEmpty(AVLTree* tree) {
    AVLForEach(*tree, AVL_TRAVERSAL_POST, AVL_LEFT, _AVLEmpty_free);
    tree->root = NULL;
}
