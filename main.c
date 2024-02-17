#include <stdio.h>
#include <ctype.h>
#include "libs/bst.h"
#include "libs/avl.h"
#include "libs/auxiliary.h"
#include "libs/food.h"

#define BUFFER_SIZE 200 // Tamanho do buffer de arquivo


char fbuffer[BUFFER_SIZE]; // Buffer para ler linhas de arquivos

int main() {
    FILE* fhandle;

    // Abrir tabela de calorias
    fhandle = fopen("1000Shuffled.csv", "r");

    if (!fhandle) {
        printf("ERRO: Nao foi possivel abrir a tabela de calorias\n");
        return 1;
    }

    // Construir ABP com os dados da tabela de calorias
    // BinarySearchTree tree = BSTCreate();

    return 0;
}

