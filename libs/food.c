#include "food.h"
#include "string.h"


// Ler a próxima comida do arquivo `fhandle`
// Cada linha pode ter no máximo `buffer_size`-1 caracteres
// Coloca em `food_ret` a comida lida
// Retorna 0 caso houve 
enum FoodReadStatus read_next_food(FILE* fhandle, Food* food_ret, size_t buffer_size) {
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
