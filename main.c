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
int comp_ABP = 0, comp_AVL = 0; // Contadores de comparações para cada árvore, conforme as especificações do trabalho

// Funções de 'consulta' de cada ávore (das especificações do trabalho)
BSTNode* consulta_ABP(BSTNode *a, char *chave);
AVLNode* consulta_AVL(AVLNode *a, char *chave);


int main(int argc, char* argv[]) {
    char *calories_filename, *consumption_filename, *report_filename;
    BinarySearchTree bst = BSTCreate();
    AVLTree avl = AVLCreate();

    /* Ler argumentos da linha de comando */
    switch (argc) {
        case 1:
        case 2:
            printf("ERRO: Faltam argumentos.\n");
            return 1;

        case 3:
            calories_filename = argv[1];
            consumption_filename = argv[2];
            report_filename = "report.log"; // Nome padrão
            break;

        case 4:
            calories_filename = argv[1];
            consumption_filename = argv[2];
            report_filename = argv[3];
            break;
    }


    /* Ler tabela de calorias */
    {
        FILE* calories_file = fopen(calories_filename, "r");

        if (!calories_file) {
            printf("ERRO: Nao foi possivel abrir a tabela de calorias.\n");
            return 1;
        }

        // Carregar tabela de calorias nas árvores
        enum FoodReadStatus status;
        Food current_food;

        while ((status = FoodReadNext(calories_file, &current_food, BUFFER_SIZE)) == FOOD_READ_OK) {
            BSTInsert(&bst, current_food);
            AVLInsert(&avl, current_food);
        }
        
        if (status == FOOD_READ_ERROR) {
            printf("ERRO: Tabela de calorias tem linhas invalidas\n");
            return 1;
        }

        fclose(calories_file);
    }

    
    /* Ler alimentos ingeridos e escrever o relatório */
    {
        FILE* consumption_file = fopen(consumption_filename, "r"); // Alimentos ingeridos

        if (!consumption_file) {
            printf("ERRO: Nao foi possivel abrir o arquivo de alimentos ingeridos.\n");
            return 1;
        }

        FILE* report_file = fopen(report_filename, "w"); // Relatório

        if (!report_file) {
            printf("ERRO: Nao foi possivel criar arquivo de saida.\n");
            return 1;
        }
    
        // Cabeçalho do arquivo de saída
        fprintf(report_file, "Calorias calculadas para `%s` usando a tabela `%s`.\n\n", consumption_filename, calories_filename);

        float total_calories = 0.0f;
        enum FoodReadStatus status;
        bool error = false; // Flag de erro

        for (;;) {
            Food current_food;
            status = FoodReadNext(consumption_file, &current_food, BUFFER_SIZE);
            bool leave = false; // Flag para parar de ler

            switch (status) {
                case FOOD_READ_ERROR:
                case FOOD_READ_EOF: // Parar de ler
                    leave = true;
                    break;

                case FOOD_READ_SKIP: // Pular linha
                    continue;

                case FOOD_READ_OK: // Ler linha
                    break;
            }

            if (leave) {
                break;
            }

            foodv_t quantity = current_food.value; // Quantidade ingerida, em gramas
            BSTNode* node = consulta_ABP(bst.root, current_food.name);
            foodv_t calories_per_portion = node->data.value; // Calorias a cada 100g
            float partial_calories = quantity * calories_per_portion / 100.0f; // Calorias adicionadas pelo item consumido
            total_calories += partial_calories; // Adicionar ao total de calorias ingeridas
            
            consulta_AVL(avl.root, current_food.name); // Utilizar AVL para contar comparações

            // Registro da consulta no relatório
            fprintf(
                report_file,
                "%dg de %s (%d calorias por 100g) = %.2f calorias\n",
                quantity,
                current_food.name,
                calories_per_portion,
                partial_calories
            );
        }
        
        fclose(consumption_file); // Fechar arquivo de alimentos ingeridos

        if (error) {
            printf("ERRO: Tabela de alimentos ingeridos tem linhas invalidas\n");
            return 1;
        }

        fprintf(report_file, "\nTotal de %.2f calorias consumidas no dia.\n\n", total_calories);

        // Estatísticas das árvores
        fprintf(report_file, "======== ESTATÍSTICAS ABP ============\n");
        fprintf(report_file, "Número de nodos: %d\n", BSTCount(bst));
        fprintf(report_file, "Altura: %d\n", BSTHeight(bst));
        fprintf(report_file, "Rotações: 0\n");
        fprintf(report_file, "Comparações: %d\n\n", comp_ABP);

        // TODO: Estatísticas da AVL
        fprintf(report_file, "======== ESTATÍSTICAS AVL ============\n");
        fprintf(report_file, "Número de nodos: %d\n", AVLCount(avl));
        fprintf(report_file, "Altura: %d\n", AVLHeight(avl));
        fprintf(report_file, "Rotações: %d\n", AVLGetRotations());
        fprintf(report_file, "Comparações: %d\n", comp_AVL);

        fclose(report_file);
    }

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