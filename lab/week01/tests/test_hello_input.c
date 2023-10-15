#include "unity.h"
#include "hello_input.c"

void setUp() {}

void tearDown() {}

void test_hello_input() {
    // Redirect stdin and stdout for input/output capture
    freopen("input.txt", "w", stdin);
    freopen("output.txt", "w", stdout);
    
    // Provide input data
    fprintf(stdin, "Alice\n");
    
    main(); // Call the main function
    
    fflush(stdout); // Flush stdout
    fclose(stdout); // Close stdout

    // Open the output file and assert the content
    FILE *output = fopen("output.txt", "r");
    TEST_ASSERT_NOT_NULL(output);
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), output);
    
    TEST_ASSERT_EQUAL_STRING("Enter your name: Hello, Alice!\n", buffer);
    
    fclose(output);
    
    // Close the input file
    fclose(stdin);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_hello_input);
    return UNITY_END();
}
