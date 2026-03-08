#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h> /* For bool (C99+) */
#include <stddef.h>  /* For size_t */
#include <stdint.h>

/* Function prototypes */
void hello(void);
void greet(const char* name);

/* Utility functions */
bool is_valid_string(const char* str);
size_t safe_strlen(const char* str);

void print_numbers(const uint8_t numbers[], const size_t numbers_size);

/* Constants */
#define MAX_NAME_LENGTH 256

#endif /* MAIN_H */
