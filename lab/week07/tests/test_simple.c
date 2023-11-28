#include <stdbool.h>
#include "unity/unity.h"

#include "../simple.c"

void setUp() {}

void tearDown() {}

void test_find_max()
{
    // Test when the first number is greater
    TEST_ASSERT_EQUAL_MESSAGE(5, find_max(5, 2), "Input: 5, 2");

    // Test when the second number is greater
    TEST_ASSERT_EQUAL_MESSAGE(8, find_max(3, 8), "Input: 3, 8");

    // Test when both numbers are equal
    TEST_ASSERT_EQUAL_MESSAGE(10, find_max(10, 10), "Input: 10, 10");
}

void test_calculate_sum()
{
    // Test with n = 5
    TEST_ASSERT_EQUAL_MESSAGE(15, calculate_sum(5), "Input: 5");

    // Test with n = 10
    TEST_ASSERT_EQUAL_MESSAGE(55, calculate_sum(10), "Input: 10");

    // Test with n = 1
    TEST_ASSERT_EQUAL_MESSAGE(1, calculate_sum(1), "Input: 1");
}

void test_array_sum()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, -5, 8, 2};
    int arr3[] = {0, 0, 0, 0, 0};

    // Test with arr1
    TEST_ASSERT_EQUAL_MESSAGE(15, array_sum(arr1, 5), "Input: {1, 2, 3, 4, 5}");

    // Test with arr2
    TEST_ASSERT_EQUAL_MESSAGE(15, array_sum(arr2, 4), "Input: {10, -5, 8, 2}");

    // Test with arr3 (all zeros)
    TEST_ASSERT_EQUAL_MESSAGE(0, array_sum(arr3, 5), "Input: {0, 0, 0, 0, 0}");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_find_max);
    RUN_TEST(test_calculate_sum);
    RUN_TEST(test_array_sum);
    return UNITY_END();
}
