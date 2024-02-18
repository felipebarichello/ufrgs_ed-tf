#include <stdio.h>
#include <ctype.h>
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
BSTNode* search_ABP(BSTNode *a, char *chave);
AVLNode* search_AVL(AVLNode *a, char *chave);


int main() {
    FILE *fhandle_in, *fhandle_out;
    Food food_buf;
    int status, calories, grams, food_cal, total_calories=0;

    BinarySearchTree tree_1;
    BSTNode *node_buf;
    AVLTree tree_2;

    // Abrir tabela de calorias
    fhandle_in = fopen("1000Shuffled.csv", "r");

    if (!fhandle_in) {
        printf("ERRO: Nao foi possivel abrir a tabela de calorias.\n");
        return 1;
    }

    // Construir ABP com os dados da tabela de calorias
    // BinarySearchTree tree = BSTCreate();


    // Abertura do arquivo de alimentos ingeridos
    fhandle_in = fopen("day1.csv", "r");
    // Criação do arquivo de saída
    fhandle_out = fopen("saída_day1.txt", "w");
    
    if (!fhandle_in) {
        printf("ERRO: Nao foi possivel abrir o arquivo de alimentos ingeridos.");
        return 1;
    }
    if (!fhandle_out) {
        printf("ERRO: Nao foi possivel criar arquivo de saida.");
        return 1;
    }

    // Registro do cabeçalho do arquivo de saída [MUDAR NOMES PARA VARIÁVEIS]
    fprintf(fhandle_out, "Calorias calculadas para day1.csv usando a tabela 1000shuffled.csv.\n");
    putc('\n', fhandle_out);

    while ((status = read_next_food(fhandle_in, &food_buf, BUFFER_SIZE)) == FOOD_READ_OK) {
        status = read_next_food(fhandle_in, &food_buf, BUFFER_SIZE);
        if (status != FOOD_READ_ERROR) {

            // Análise dos dados do arquivo
            grams = food_buf.value;

            node_buf = search_ABP(tree_1, food_buf.name);    // consulta com a árvore 1, BTS 
            search_AVL(tree_2, food_buf.name);     // consulta com a árvore 2, AVL (sem armazenar resultado)

            calories = node_buf->data.value;
            food_cal = grams*calories
            total_calories += food_cal;

            // Registro da consulta/análise no arquivo de saída
            fprintf(fhandle_out, "%dg de %s (%d calorias por 100g) = %d calorias\n", grams, food_buf.name, calories, food_cal);

        } else {
            printf(“Linha com valores inválidos.”);
            return 1;
        }

        // Fecha o arquivo de alimentos ingeridos
        fclose(fhandle_in);

        // Completa o arquivo de saída
        putc('\n', fhandle_out);
        fprintf(fhandle_out, "Total de %d calorias consumidas no dia.\n", total_calories);
        putc('\n', fhandle_out);

        fprintf(fhandle_out, "======== ESTATÍSTICAS ABP ============\n");
        fprintf(fhandle_out, "Número de nodos: %d\n", _);
        fprintf(fhandle_out, "Altura: %d\n", _);
        fprintf(fhandle_out, "Rotações: 0\n");
        fprintf(fhandle_out, "Comparações: %d\n", comp_ABP);
        putc('\n', fhandle_out);

        fprintf(fhandle_out, "======== ESTATÍSTICAS AVL ============\n");
        fprintf(fhandle_out, "Número de nodos: %d\n", _);
        fprintf(fhandle_out, "Altura: %d\n", _);
        fprintf(fhandle_out, "Rotações: %d\n", _);
        fprintf(fhandle_out, "Comparações: %d\n", comp_AVL);

        // Fecha o arquivo de saída
        fclose(fhandle_out);
    }


    return 0;
}


// Função 'consulta' das especificações do trabalho, com apenas os nomes alterados
BSTNode* search_ABP(BSTNode *a, char *chave) {

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

AVLNode* search_AVL(AVLNode *a, char *chave) {

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