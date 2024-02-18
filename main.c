#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
    Food current_food;


    // Ler tabela de calorias
    fhandle = fopen("tests\\1000Shuffled.csv", "r"); // TODO: Utilizar arquivo fornecido pela linha de comando

    if (!fhandle) {
        printf("ERRO: Nao foi possivel abrir a tabela de calorias\n");
        return 1;
    }

    // TODO: Inserir nas árvores

    fclose(fhandle);

    
    // Ler alimentos ingeridos
    AVLTree avl = AVLCreate();
    fhandle = fopen("tests\\day1.csv", "r"); // TODO: Utilizar arquivo fornecido pela linha de comando

    if (!fhandle) {
        printf("ERRO: Nao foi possivel abrir a tabela de alimentos ingeridos\n");
        return 1;
    }

    enum FoodReadStatus status;
    foodv_t total_calories = 0;
    while ((status = FoodReadNext(fhandle, &current_food, BUFFER_SIZE)) == FOOD_READ_OK) {
        if (status == FOOD_READ_ERROR) {
            printf("ERRO: Tabela de alimentos ingeridos tem linhas invalidas\n");
            return 1;
        }

        foodv_t quantity = current_food.value; // Quantidade ingerida, em gramas

        AVLNode* node = consulta(avl.root, current_food.name);
        foodv_t calories_per_portion = node->data.value;
        total_calories += quantity * calories_per_portion;
    }

    fclose(fhandle);

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
