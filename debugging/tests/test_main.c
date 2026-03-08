#include "../include/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Simple test framework macros */
#define ASSERT_TRUE(expr) do { \
    if (!(expr)) { \
        fprintf(stderr, "FAIL: %s at %s:%d\n", #expr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))
#define ASSERT_EQ(a, b) ASSERT_TRUE((a) == (b))

/* Test functions */
static void test_is_valid_string(void) {
    printf("Testing is_valid_string... ");

    ASSERT_TRUE(is_valid_string("hello"));
    ASSERT_FALSE(is_valid_string(NULL));
    ASSERT_FALSE(is_valid_string(""));

    printf("PASSED\n");
}

static void test_safe_strlen(void) {
    printf("Testing safe_strlen... ");

    ASSERT_EQ(safe_strlen("hello"), 5);
    ASSERT_EQ(safe_strlen(""), 0);
    ASSERT_EQ(safe_strlen(NULL), 0);

    printf("PASSED\n");
}

int main(void) {
    printf("Running C project tests...\n\n");

    test_is_valid_string();
    test_safe_strlen();

    printf("\nAll tests passed!\n");
    return EXIT_SUCCESS;
}
