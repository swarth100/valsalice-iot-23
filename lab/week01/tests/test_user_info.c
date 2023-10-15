#include "unity.h"
#include "user_info.c"

void setUp() {}

void tearDown() {}

void test_user_info() {
    // Redirect stdin and stdout for input/output capture
    freopen("input.txt", "w", stdin);
    freopen("output.txt", "w", stdout);
    
    // Provide input data
    fprintf(stdin, "Alice\n");
    fprintf(stdin, "25\n");
    fprintf(stdin, "1.65\n");
    
    main(); // Call the main function
    
    fflush(stdout); // Flush stdout
    fclose(stdout); // Close stdout

    // Open the output file and assert the content
    FILE *output = fopen("output.txt", "r");
    TEST_ASSERT_NOT_NULL(output);
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), output);
    
    TEST_ASSERT_EQUAL_STRING("Enter your name: Enter your age: Enter your height in meters: User is named Alice with age 25 and height 1.65 meters.\n", buffer);
    
    fclose(output);
    
    // Close the input file
    fclose(stdin);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_user_info);
    return UNITY_END();
}
