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

timespec time_add(timespec a, timespec b) {
    timespec result;

    result.tv_sec = a.tv_sec + b.tv_sec;
    result.tv_nsec = a.tv_nsec + b.tv_nsec;

    if (result.tv_nsec >= 1000000000) {
        result.tv_sec++;
        result.tv_nsec -= 1000000000;
    }

    return result;
}

timespec time_diff(timespec a, timespec b) {
    timespec result;

    result.tv_sec = a.tv_sec - b.tv_sec;
    result.tv_nsec = a.tv_nsec - b.tv_nsec;

    if (result.tv_nsec < 0) {
        result.tv_sec--;
        result.tv_nsec += 1000000000;
    }

    return result;
}
