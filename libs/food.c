#include <stdlib.h>
#include "food.h"
#include "string.h"
#include "auxiliary.h"


bool FoodIsEqual(Food a, Food b) {
    return strcmp(a.name, b.name) == 0;
}

bool FoodIsLower(Food a, Food b) {
    return strcmp(a.name, b.name) < 0;
}

bool FoodIsGreater(Food a, Food b) {
    return strcmp(a.name, b.name) > 0;
}

enum FoodReadStatus FoodReadNext(FILE* fhandle, Food* food_ret, size_t buffer_size) {
    char buffer[buffer_size];

    char* result = fgets(buffer, buffer_size, fhandle); // Ler linha do arquivo `fhandle`

    if (!result) { // Fim do arquivo
        return 0;
    }

    // Separar o nome da comida do seu valor associado
    char* food_name = strtok(buffer, ";");

    if (!food_name) {
        return FOOD_READ_ERROR;
    }

    char* value_str = strtok(NULL, NULL); // String com o valor

    if (!value_str) {
        return FOOD_READ_ERROR;
    }

    // Pré-processar os valores
    foodv_t value = atoi(value_str);
    str_tolower(food_name); // Case insensitivity

    // Retornar a comida lida
    Food food;
    strcpy(food.name, food_name);
    food.value = atoi(value_str);
    *food_ret = food;

    return result ? FOOD_READ_OK : FOOD_READ_EOF;
}
