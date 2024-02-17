#include <stdio.h>
#include <ctype.h>
#include "libs/bst.h"
#include "libs/avl.h"
#include "libs/auxiliary.h"
#include "libs/food.h"

#define BUFFER_SIZE 200 // Tamanho do buffer de arquivo


// Variáveis globais
char fbuffer[BUFFER_SIZE]; // Buffer para ler linhas de arquivos
int comp = 0; // Contador de comparações, conforme especificado nas especificações do trabalho

// Função `consulta` das especificações do trabalho
AVLNode* consulta(AVLNode *a, char *chave);


int main() {
    FILE* fhandle;
    Food food_buf;
    AVLTree tree_1;
    AVLNode* node_buf;
    int status, calories, grams, total_calories=0;

    // Abrir tabela de calorias
    fhandle = fopen("1000Shuffled.csv", "r");

    if (!fhandle) {
        printf("ERRO: Nao foi possivel abrir a tabela de calorias\n");
        return 1;
    }

    // Construir ABP com os dados da tabela de calorias
    // BinarySearchTree tree = BSTCreate();

    
    // Abertura do arquivo de alimentos ingeridos
    fhandle = fopen("day1.csv", "r");

    if (fhandle) {
        while ((status = read_next_food(fhandle, &food_buf, BUFFER_SIZE)) == FOOD_READ_OK) {
            status = read_next_food(fhandle, &food_buf, BUFFER_SIZE);
            if (status != FOOD_READ_ERROR) {
                grams = food_buf->value;
                node_buf = consulta(tree_1, food_buf.name);
                calories = node_buf->data.value;
                total_calories += grams*calories;
            } else {
                printf(“Linha com valores inválidos.”);
                return 1;
            }
        }
    } else {
        printf(“Erro na abertura do arquivo.”);
    }

    return 0;
}


// Função `consulta` das especificações do trabalho, com apenas os nomes alterados
AVLNode* consulta(AVLNode *a, char *chave) {
    while (a != NULL){
        comp++;
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
