#pragma once

#include <stdio.h>

typedef unsigned int foodv_t;

typedef struct Food {
    char* name;
    foodv_t value;
} Food;

enum FoodReadStatus {
    FOOD_READ_OK,
    FOOD_READ_EOF,
    FOOD_READ_ERROR
};

enum FoodReadStatus read_next_food(FILE* fhandle, Food* food_ret, size_t buffer_size);
