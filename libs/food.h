#pragma once

#include <stdio.h>
#include <stdbool.h>


typedef unsigned int foodv_t;

typedef struct Food {
    char* name;
    foodv_t value;
} Food;

enum FoodReadStatus {
    FOOD_READ_OK,
    FOOD_READ_EOF,
    FOOD_READ_ERROR,
    FOOD_READ_SKIP
};

// Comparações entre comidas
bool FoodIsEqual(Food a, Food b);
bool FoodIsLower(Food a, Food b);
bool FoodIsGreater(Food a, Food b);

// Ler a próxima comida do arquivo `fhandle`
// Cada linha pode ter no máximo `buffer_size`-1 caracteres
// Coloca em `food_ret` a comida lida
// Retorna 0 caso houve 
enum FoodReadStatus FoodReadNext(FILE* fhandle, Food* food_ret, size_t buffer_size);
