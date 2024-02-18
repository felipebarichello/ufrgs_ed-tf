// Funções auxiliares

#pragma once

#include <time.h>

typedef struct timespec timespec;

void str_tolower(char *string_buffer);

timespec time_add(timespec a, timespec b);
timespec time_diff(timespec a, timespec b);
