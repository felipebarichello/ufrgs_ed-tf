#include "auxiliary.h"

void str_tolower(char *string_buffer) { // TODO: não testado
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
