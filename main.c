#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libs/bst.h"
#include "libs/avl.h"
#include "libs/auxiliary.h"
#include "libs/food.h"

#define BUFFER_SIZE 200 // Tamanho do buffer de arquivo


// Variáveis globais:
char fbuffer[BUFFER_SIZE]; // Buffer para ler linhas de arquivos
int comp_ABP = 0;       // Contadores de comparações para cada árvore
int comp_AVL = 0;  

// Funções de 'consulta' de cada ávore (das especificações do trabalho)
BSTNode* consulta_ABP(BSTNode *a, char *chave);
AVLNode* consulta_AVL(AVLNode *a, char *chave);


int main() {
    FILE* fhandle;
    Food current_food;


    // Ler tabela de calorias
    fhandle = fopen("tests\\1000Shuffled.csv", "r"); // TODO: Utilizar arquivo fornecido pela linha de comando

    if (!fhandle) {
        printf("ERRO: Nao foi possivel abrir a tabela de calorias.\n");
        return 1;
    }

    // TODO: Inserir nas árvores

    fclose(fhandle);

    
    // Ler alimentos ingeridos
    // TODO: Utilizar arquivo fornecido pela linha de comando
    fhandle = fopen("tests\\day1.csv", "r"); // Alimentos ingeridos

    if (!fhandle) {
        printf("ERRO: Nao foi possivel abrir o arquivo de alimentos ingeridos.\n");
        return 1;
    }

    // TODO: Utilizar arquivo fornecido pela linha de comando
    FILE* fhandle_report = fopen("tests\\saída_day1.txt", "w"); // Relatório

    if (!fhandle_report) {
        printf("ERRO: Nao foi possivel criar arquivo de saida.\n");
        return 1;
    }
    
    // TODO: AVL
    BinarySearchTree bst = BSTCreate();

    // Cabeçalho do arquivo de saída
    // TODO: Utilizar arquivo fornecido pela linha de comando
    fprintf(fhandle_report, "Calorias calculadas para day1.csv usando a tabela 1000shuffled.csv.\n");

    enum FoodReadStatus status;
    foodv_t total_calories = 0;

    while ((status = FoodReadNext(fhandle, &current_food, BUFFER_SIZE)) == FOOD_READ_OK) {
        if (status == FOOD_READ_ERROR) {
            printf("ERRO: Tabela de alimentos ingeridos tem linhas invalidas\n");
            fprintf(fhandle_report, "ERRO: Tabela de alimentos ingeridos tem linhas invalidas\n");
            return 1;
        }

        foodv_t quantity = current_food.value; // Quantidade ingerida, em gramas
        BSTNode* node = consulta_ABP(bst.root, current_food.name);
        foodv_t calories_per_portion = node->data.value; // Calorias a cada 100g
        foodv_t partial_calories = quantity * calories_per_portion; // Calorias adicionadas pelo item consumido
        total_calories += partial_calories; // Adicionar ao total de calorias ingeridas

        // Registro da consulta no relatório
        fprintf(
            fhandle_report,
            "%dg de %s (%d calorias por 100g) = %d calorias\n",
            quantity,
            current_food.name,
            calories_per_portion,
            partial_calories
        );
    }

    fclose(fhandle); // Fechar arquivo de alimentos ingeridos

    fprintf(fhandle_report, "\nTotal de %d calorias consumidas no dia.\n\n", total_calories);

    // Estatísticas das árvores
    // TODO: Estatísticas da ABP
    // fprintf(fhandle_report, "======== ESTATÍSTICAS ABP ============\n");
    // fprintf(fhandle_report, "Número de nodos: %d\n", _);
    // fprintf(fhandle_report, "Altura: %d\n", _);
    // fprintf(fhandle_report, "Rotações: 0\n");
    // fprintf(fhandle_report, "Comparações: %d\n\n", comp_ABP);

    // TODO: Estatísticas da AVL
    // fprintf(fhandle_report, "======== ESTATÍSTICAS AVL ============\n");
    // fprintf(fhandle_report, "Número de nodos: %d\n", _);
    // fprintf(fhandle_report, "Altura: %d\n", _);
    // fprintf(fhandle_report, "Rotações: %d\n", _);
    // fprintf(fhandle_report, "Comparações: %d\n", comp_AVL);

    fclose(fhandle_report);

    return 0;
}


// Função `consulta` que deve ser usada, segundo as especificações do trabalho.
// A função foi dividida em duas, uma para cada árvore.
// As únicas diferenças entre a função das especificações e a função abaixo são:
// 1. Todas as instâncias de `pNodoA` foram substituídas por `BSTNode` ou `AVLNode`;
// 2. A formatação (espaços e tabs; as quebras de linha foram preservadas);
// 3. Todas as instâncias de `a->alimento` foram substituídas por `a->data.name`.
BSTNode* consulta_ABP(BSTNode *a, char *chave) {
    while (a != NULL){
        comp_ABP++;
        if (!strcmp(a->data.name, chave)){
            return a;
        }
        else {
            if (strcmp(a->data.name, chave) > 0)
                a = a->left;
            else
                a = a->right;
        }
    }
    return NULL;
}

AVLNode* consulta_AVL(AVLNode *a, char *chave) {
    while (a != NULL){
        comp_AVL++;
        if (!strcmp(a->data.name, chave)){
            return a;
        }
        else {
            if (strcmp(a->data.name, chave) > 0)
                a = a->left;
            else
                a = a->right;
        }
    }
    return NULL;
}