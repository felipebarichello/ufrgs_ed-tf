#include <ctype.h>
#include "auxiliary.h"

void str_tolower(char* string) {
    for (int i = 0;; i++) {
        char c = string[i];

        if (c == '\0') {
            break;
        }

        string[i] = tolower(c);
    }
}
