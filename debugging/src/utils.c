#include "main.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void print_numbers(const uint8_t numbers[], const size_t numbers_size) {
    for (size_t i = 0; i < numbers_size; i++) {
#ifdef DEBUG_ADD
        printf("%i \n", numbers[i]);
#else
        printf("%i\n", numbers[i] ^ 2);
#endif
    }
}

void hello(void) {
    puts("Hello, World!"); /* puts is safer than printf for simple strings */
}

void greet(const char* name) {
    if (!is_valid_string(name)) {
        fprintf(stderr, "Error: Invalid name provided\n");
        return;
    }

    printf("Hello, %s!\n", name);
}

bool is_valid_string(const char* str) {
    return str != NULL && strlen(str) > 0;
}

size_t safe_strlen(const char* str) {
    return str ? strlen(str) : 0;
}
