// Árvore AVL

#pragma once


// Tipo concreto de dado armazenado na árvore
typedef int avldata_t;

// Tipo concreto da altura da árvore
typedef unsigned short avlheight_t;

// Nodo da árvore binária
// `height` é a altura do nodo.
// É mais eficiente armazenar a altura do nodo que calcular a altura cada vez.
typedef struct AVLNode {
    avldata_t data;
    avlheight_t height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// A árvore binária é apenas um encapsulamento de um nodo que pode agir como raíz
// Note qualquer nodo é também uma árvore binária
// Para utilizar funções que operam em árvores binárias fora da raíz, basta chamar AVLFromNode(nodo)
typedef struct AVLTree {
    AVLNode* root;
} AVLTree;

// Lado que o filho está
enum AVLSide {
    AVL_LEFT,
    AVL_RIGHT
};

// Ordem do caminhamento
enum AVLTraversal {
    AVL_TRAVERSAL_PRE,
    AVL_TRAVERSAL_IN,
    AVL_TRAVERSAL_POST
};


// Criar e alocar um novo nodo sem filhos na heap
// Retorna o nodo criado
AVLNode* AVLNewNode(avldata_t data);

// Criar uma árvore vazia
AVLTree AVLCreate();

// Criar uma nova árvore a partir de um nodo que será a raíz da árvore
AVLTree AVLFromNode(AVLNode* root);

// Verificar se a árvore binária está vazia
avldata_t AVLIsEmpty(AVLTree tree);

// Inserir item na lista em ordem crescente
// Usar essa função para inserir itens na árvore
// Retorna o nodo do item inserido
// Não verifica se `tree` é NULL
AVLNode* AVLInsert(AVLTree* tree, avldata_t data);

// Buscar item na lista
// Retorna o nodo do item encontrado ou NULL caso não encontre
AVLNode* AVLSearch(AVLTree tree, avldata_t data);

// Caminhar por todos os itens da árvore, executando a função `operation`
// `operation` deve retornar 0 para continuar o caminhamento ou 1 para parar
// `traversal` define a ordem do caminhamento e `order` define a ordem dos filhos
// Retorna 1 se o caminhamento foi interrompido pela função `operation` e 0 caso contrário
// Não verifica se `tree` é NULL
// Cuidado para não remover a raíz da árvore durante o caminhamento
// Cuidado com o balanceamento da árvore
// Antes de usar, verifique se não há outras funções que possam fazer o que você quer, pois ela não é muito eficiente
int AVLForEach(AVLTree tree, enum AVLTraversal traversal, enum AVLSide order, int (*operation)(AVLNode* node));

// Contar quantos itens a árvore possui
int AVLCount(AVLTree tree);

// Retorna a altura do nodo
avlheight_t AVLNodeHeight(AVLNode* node);

// Atualizar altura do nodo
avlheight_t AVLUpdateHeight(AVLNode* node);

// Calcular fator de balanceamento da árvore
int AVLBalanceFactor(AVLTree tree);

// Calcular fator de balanceamento do nodo
int AVLNodeBalanceFactor(AVLNode* node);

// Imprimir árvore
// Encapsulamento sobre AVLForEach() para imprimir a árvore
void AVLPrintList(AVLTree tree, enum AVLTraversal traversal, enum AVLSide order);

// Imprimir a árvore em um formato visual
void AVLDraw(AVLTree tree);

// Romover item da lista
// Retorna 1 se encontrou o produto, 0 caso contrário
int AVLRemove(AVLTree* tree, avldata_t data);

// Esvazia a árvore
void AVLEmpty(AVLTree* tree);
