#include <stdio.h>
#include <ctype.h>
#include "trees/bst.h"
#include "trees/avl.h"

#define BUFFER_SIZE 200

int comp = 0;


void lower_string (char *string_buffer);
AVLNode* consulta(AVLNode *a, char *chave);

int main() {
    FILE *fhandle;
    Food food_buf;
    AVLTree tree_1;
    AVLNode *node_buf;
    int status, calories, grams, total_calories=0;

    // Abertura do arquivo de alimentos ingeridos
    fhandle = fopen("day1.csv", r);

    if (fhandle) {
        while ((status = read_next_food(fhandle, &food_buf, BUFFER_SIZE)) == FOOD_READ_OK) {
            status = read_next_food(fhandle, &food_buf, BUFFER_SIZE);
            if (status != FOOD_READ_ERROR) {
                grams = food_buf->value;
                node_buf = consulta(tree_1, food_buf.name);
                calories = node->data.value;
                total_calories += grams*calories;
            } else {
                printf(“Linha com valores inválidos.”);
                return 1;
            }
        }
    } else 
        printf(“Erro na abertura do arquivo.”);

    return 0;
}

void lower_string (char *string_buffer) {
    int i=0;
    char c;

    c = string_buffer[i];
    while (c != '\0') {
        tolower(c);
        string_buffer[i] = c;

        i++;
        c = string_buffer[i];
    }
}

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