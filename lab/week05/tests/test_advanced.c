#include <stdbool.h>
#include "unity/unity.h"

#include "../advanced.c"

void setUp() {}

void tearDown() {}

void test_next_even()
{
    TEST_ASSERT_EQUAL_MESSAGE(2, next_even(0), "Input: 0");
    TEST_ASSERT_EQUAL_MESSAGE(4, next_even(3), "Input: 3");
    TEST_ASSERT_EQUAL_MESSAGE(6, next_even(5), "Input: 5");
    TEST_ASSERT_EQUAL_MESSAGE(100, next_even(99), "Input: 99");
}

void test_factorial()
{
    TEST_ASSERT_EQUAL_MESSAGE(1, factorial(0), "Input: 0");
    TEST_ASSERT_EQUAL_MESSAGE(1, factorial(1), "Input: 1");
    TEST_ASSERT_EQUAL_MESSAGE(2, factorial(2), "Input: 2");
    TEST_ASSERT_EQUAL_MESSAGE(6, factorial(3), "Input: 3");
    TEST_ASSERT_EQUAL_MESSAGE(24, factorial(4), "Input: 4");
}

void test_sum_of_natural_numbers()
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, sum_of_natural_numbers(0), "Input: 0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, sum_of_natural_numbers(1), "Input: 1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(15, sum_of_natural_numbers(5), "Input: 5");
    TEST_ASSERT_EQUAL_INT_MESSAGE(28, sum_of_natural_numbers(7), "Input: 7");
}

void test_is_prime()
{
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(0), "Input: 0");
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(1), "Input: 1");
    TEST_ASSERT_EQUAL_MESSAGE(true, is_prime(2), "Input: 2");
    TEST_ASSERT_EQUAL_MESSAGE(true, is_prime(3), "Input: 3");
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(4), "Input: 4");
    TEST_ASSERT_EQUAL_MESSAGE(true, is_prime(5), "Input: 5");
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(6), "Input: 6");
    TEST_ASSERT_EQUAL_MESSAGE(true, is_prime(7), "Input: 7");
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(8), "Input: 8");
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(9), "Input: 9");
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(10), "Input: 10");
    TEST_ASSERT_EQUAL_MESSAGE(true, is_prime(11), "Input: 11");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_next_even);
    RUN_TEST(test_factorial);
    RUN_TEST(test_sum_of_natural_numbers);
    RUN_TEST(test_is_prime);
    return UNITY_END();
}
