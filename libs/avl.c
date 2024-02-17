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

// Função interna. Não exposta no header.
void _AVLRotateRight(AVLNode** subtree_root) {
    AVLNode* old_root = *subtree_root;
    AVLNode* new_root = old_root->left;
    
    *subtree_root = new_root;
    old_root->left = new_root->right;
    new_root->right = old_root;
    
    AVLNodeUpdateHeight(old_root);
    AVLNodeUpdateHeight(new_root);
}

// Função interna. Não exposta no header.
void _AVLRotateLeft(AVLNode** subtree_root) {
    AVLNode* old_root = *subtree_root;
    AVLNode* new_root = old_root->right;
    
    *subtree_root = new_root;
    old_root->right = new_root->left;
    new_root->left = old_root;

    AVLNodeUpdateHeight(old_root);
    AVLNodeUpdateHeight(new_root);
}

// Balancear a subárvore após inserção
// Pode modificar o ponteiro `subtree` para apontar para outro nodo
// Retorna 1 se houve balanceamento, 0 caso contrário
// Função interna. Não exposta no header.
void _AVLBalanceAfterInsertion(AVLNode** subtree, avldata_t data) {
    int balance_factor = AVLNodeBalanceFactor(*subtree);
    
    if (balance_factor > 1) {
        // A subárvore esquerda é mais alta
        AVLNode** tallest_child_slot = &(*subtree)->left;

        if (data > (*tallest_child_slot)->data) {
            // Rotação dupla
            _AVLRotateLeft(tallest_child_slot);
        }

        _AVLRotateRight(subtree);
    } else if (balance_factor < -1) {
        // A subárvore direita é mais alta
        AVLNode** tallest_child_slot = &(*subtree)->right;
        
        if (data < (*tallest_child_slot)->data) {
            // Rotação dupla
            _AVLRotateRight(tallest_child_slot);
        }

        _AVLRotateLeft(subtree);
    }
}

// Função interna recursiva para AVLInsert()
// Não exposta no header
AVLNode* _AVLInsert(AVLNode* node, avldata_t data) {
    // `&node->left` ou `&node->right`, dependendo do valor de `data`
    AVLNode** relevant_child;

    if (data < node->data) {
        relevant_child = &node->left;
    } else if (data > node->data) {
        relevant_child = &node->right;
    } else {
        // Valor repetido. Não inserir.
        return NULL;
    }

    if (!*relevant_child) {
        AVLNode* new_node = AVLNewNode(data);
        *relevant_child = new_node;
        AVLNodeUpdateHeight(node);

        // Não é necessário balancear, pois é impossível o nodo pai do novo nodo estar desbalanceado.
        return new_node;
    }

    AVLNode* ret = _AVLInsert(*relevant_child, data);

    // Balancear o filho
    // É o pai quem deve balancear o filho para poder tratar situações em que ele deve trocar o filho
    _AVLBalanceAfterInsertion(relevant_child, data);

    // Atualizar própria altura
    if (ret) {
        AVLNodeUpdateHeight(node);
    }

    return ret;
}

AVLNode* AVLInsert(AVLTree* tree, avldata_t data) {
    if (AVLIsEmpty(*tree)) {
        tree->root = AVLNewNode(data);
        return tree->root;
    }

    // Inserir recursivamente
    AVLNode* new_node = _AVLInsert(tree->root, data);

    // Balancear a raiz
    _AVLBalanceAfterInsertion(&tree->root, data);

    return new_node;
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

avlheight_t AVLNodeUpdateHeight(AVLNode* node) {
    avlheight_t lheight = node->left  ? AVLNodeHeight(node->left)  : 0;
    avlheight_t rheight = node->right ? AVLNodeHeight(node->right) : 0;

    if (lheight > rheight) {
        node->height = lheight + 1;
    } else {
        node->height = rheight + 1;
    }

    return node->height;
}

// Função interna recursiva para AVLTreeBalanceFactor()
// Não exposta no header
int _AVLTreeBalanceFactor(AVLNode* node) {
    if (!node) {
        return 0;
    }

    int selfbalance = abs(AVLNodeBalanceFactor(node));
    int lbalance = _AVLTreeBalanceFactor(node->left);
    int rbalance = _AVLTreeBalanceFactor(node->right);

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

int AVLTreeBalanceFactor(AVLTree tree) {
    return _AVLTreeBalanceFactor(tree.root);
}

int AVLNodeBalanceFactor(AVLNode* node) {
    int lheight = node->left  ? AVLNodeHeight(node->left)  : 0;
    int rheight = node->right ? AVLNodeHeight(node->right) : 0;
    return lheight - rheight;
}

int AVLIsNodeBalanced(AVLNode* node) {
    avlheight_t balance_factor = AVLNodeBalanceFactor(node);
    return balance_factor <= 1 && balance_factor >= -1;
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

        printf("+- %d\n", node->data);

        if (node->left) 
            _AVLDraw(node->left, level + 1);

        if (node->right)
            _AVLDraw(node->right, level + 1);
    }
}

void AVLDraw(AVLTree tree) {
    _AVLDraw(tree.root, 1);
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
