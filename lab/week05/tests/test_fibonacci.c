#include "unity/unity.h"

#include "../fibonacci.c"

// These are required by Unity
void setUp(void) {}
void tearDown(void) {}

void test_fibonacci_basic(void)
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, fibonacci(0), "Input: 0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, fibonacci(1), "Input: 1");
}

void test_fibonacci_values(void)
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, fibonacci(2), "Input: 2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, fibonacci(3), "Input: 3");
    TEST_ASSERT_EQUAL_INT_MESSAGE(5, fibonacci(5), "Input: 5");
    TEST_ASSERT_EQUAL_INT_MESSAGE(21, fibonacci(8), "Input: 8");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_fibonacci_basic);
    RUN_TEST(test_fibonacci_values);

    return UNITY_END();
}
