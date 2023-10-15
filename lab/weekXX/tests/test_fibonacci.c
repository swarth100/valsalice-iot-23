#include "unity/unity.h"

#include "../fibonacci.c"

// These are required by Unity
void setUp(void) {}
void tearDown(void) {}

void test_fibonacci_basic(void) {
    TEST_ASSERT_EQUAL_INT(0, fibonacci(0));
    TEST_ASSERT_EQUAL_INT(1, fibonacci(1));
}

void test_fibonacci_values(void) {
    TEST_ASSERT_EQUAL_INT(1, fibonacci(2));
    TEST_ASSERT_EQUAL_INT(2, fibonacci(3));
    TEST_ASSERT_EQUAL_INT(5, fibonacci(5));
    TEST_ASSERT_EQUAL_INT(21, fibonacci(8));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_fibonacci_basic);
    RUN_TEST(test_fibonacci_values);

    return UNITY_END();
}
