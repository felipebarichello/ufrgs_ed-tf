// Árvore Binária de Pesquisa - Binary Search Tree (BST)

#pragma once


// Tipo concreto de dado armazenado na árvore
typedef int BSTData;

// Nodo da árvore binária
typedef struct BSTNode {
    BSTData data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// A árvore binária é apenas um encapsulamento de um nodo que pode agir como raíz
// Note qualquer nodo é também uma árvore binária
// Para utilizar funções que operam em árvores binárias fora da raíz, basta chamar BSTFromNode(nodo)
typedef struct BinarySearchTree {
    BSTNode* root;
} BinarySearchTree;

// Lado que o filho está
enum BSTSide {
    BST_LEFT,
    BST_RIGHT
};

// Ordem do caminhamento
enum BSTTraversal {
    BST_TRAVERSAL_PRE,
    BST_TRAVERSAL_IN,
    BST_TRAVERSAL_POST
};


// Criar e alocar um novo nodo sem filhos na heap
// Retorna o nodo criado
BSTNode* BSTNewNode(BSTData data);

// Criar uma árvore vazia
BinarySearchTree BSTCreate();

// Criar uma nova árvore a partir de um nodo que será a raíz da árvore
BinarySearchTree BSTFromNode(BSTNode* root);

// Verificar se a árvore binária está vazia
BSTData BSTIsEmpty(BinarySearchTree tree);

// Inserir item na lista em ordem crescente
// Usar essa função para inserir itens na árvore
// Retorna o nodo do item inserido
// Não verifica se `tree` é NULL
BSTNode* BSTInsert(BinarySearchTree* tree, BSTData data);

// Buscar item na lista
// Retorna o nodo do item encontrado ou NULL caso não encontre
BSTNode* BSTSearch(BinarySearchTree tree, BSTData data);

// Caminhar por todos os itens da árvore, executando a função `operation`
// `operation` deve retornar 0 para continuar o caminhamento ou 1 para parar
// `traversal` define a ordem do caminhamento e `order` define a ordem dos filhos
// Retorna 1 se o caminhamento foi interrompido pela função `operation` e 0 caso contrário
// Não verifica se `tree` é NULL
// Cuidado para não remover a raíz da árvore durante o caminhamento
// Antes de usar, verifique se não há outras funções que possam fazer o que você quer, pois ela não é muito eficiente
int BSTForEach(BinarySearchTree tree, enum BSTTraversal traversal, enum BSTSide order, int (*operation)(BSTNode* node));

// Contar quantos itens a árvore possui
int BSTCount(BinarySearchTree tree);

// Calcular altura do nodo
int BSTNodeHeight(BSTNode* node);

// Calcular fator de balanceamento da árvore
int BSTBalanceFactor(BinarySearchTree tree);

// Calcular fator de balanceamento do nodo
int BSTNodeBalanceFactor(BSTNode* node);

// Imprimir árvore
// Encapsulamento sobre BSTForEach() para imprimir a árvore
void BSTPrintList(BinarySearchTree tree, enum BSTTraversal traversal, enum BSTSide order);

// Imprimir a árvore em um formato visual
void BSTDraw(BinarySearchTree tree);

// Romover item da lista
// Retorna 1 se encontrou o produto, 0 caso contrário
int BSTRemove(BinarySearchTree* tree, BSTData data);

// Esvazia a árvore
void BSTEmpty(BinarySearchTree* tree);
