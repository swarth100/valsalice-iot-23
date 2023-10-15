#include "unity.h"
#include "hello_world.c"

void setUp() {}

void tearDown() {}

void test_hello_world() {
    // Redirect stdout to capture printf output
    freopen("output.txt", "w", stdout);
    main(); // Call the main function
    fflush(stdout); // Flush stdout
    fclose(stdout); // Close stdout

    // Open the output file and assert the content
    FILE *output = fopen("output.txt", "r");
    TEST_ASSERT_NOT_NULL(output);
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), output);
    
    TEST_ASSERT_EQUAL_STRING("Hello, World!\n", buffer);
    
    fclose(output);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_hello_world);
    return UNITY_END();
}
