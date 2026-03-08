#include "main.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // hello();
    // greet("Modern C");

    printf("rebuild 1?");
    uint8_t numbers[] = {1, 2, 3, 4, 5};
    print_numbers(numbers, sizeof(numbers));

    uint8_t* ptr = NULL;
    assert(ptr != NULL);

    // uint8_t* memory = (uint8_t*)malloc(sizeof(uint8_t) * 1000);
    // memory[0] = 0;
    // for (size_t i = 0; i < 1000; i++) {
    //     printf("%i", memory[i]);
    // }

    /* Demonstrate error handling */
    // greet(NULL); /* This will show error message */
    // greet("");   /* This will also show error message */

    return EXIT_SUCCESS;
}
