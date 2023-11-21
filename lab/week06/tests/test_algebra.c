#include <stdbool.h>
#include "unity/unity.h"

#include "../algebra.c"

void setUp() {}

void tearDown() {}

void test_calculate_expression()
{
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(8.0, calculate_expression(2, 3, 4), "Input: 2, 3, 4");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-4.0, calculate_expression(1, -2, 3), "Input: 1, -2, 3");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.0, calculate_expression(0, 1, 2), "Input: 0, 1, 2");
}

void test_double_or_negate()
{
    TEST_ASSERT_EQUAL_MESSAGE(4, double_or_negate(2), "Input: 2");
    TEST_ASSERT_EQUAL_MESSAGE(-3, double_or_negate(3), "Input: 3");
    TEST_ASSERT_EQUAL_MESSAGE(-5, double_or_negate(5), "Input: 5");
}

void test_sum_or_min()
{
    TEST_ASSERT_EQUAL_MESSAGE(15, sum_or_min(7, 8), "Input: 7, 8");
    TEST_ASSERT_EQUAL_MESSAGE(7, sum_or_min(7, 100), "Input: 7, 100");
    TEST_ASSERT_EQUAL_MESSAGE(50, sum_or_min(50, 60), "Input: 50, 60");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_calculate_expression);
    RUN_TEST(test_double_or_negate);
    RUN_TEST(test_sum_or_min);
    return UNITY_END();
}
