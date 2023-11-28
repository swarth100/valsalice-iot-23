#include <stdbool.h>
#include "unity/unity.h"

#include "../advanced.c"

void setUp() {}

void tearDown() {}

void test_replace_even_with_8()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, -5, 8, 2};
    int arr3[] = {0, 0, 0, 0, 0};

    int expected_arr1[] = {8, 2, 8, 4, 8};
    int expected_arr2[] = {8, -5, 8, 2};
    int expected_arr3[] = {8, 0, 8, 0, 8};

    // Test with arr1
    replace_even_with_8(arr1, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected_arr1, arr1, 5, "Input: {1, 2, 3, 4, 5}");

    // Test with arr2
    replace_even_with_8(arr2, 4);
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected_arr2, arr2, 4, "Input: {10, -5, 8, 2}");

    // Test with arr3 (all zeros)
    replace_even_with_8(arr3, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected_arr3, arr3, 5, "Input: {0, 0, 0, 0, 0}");
}

void test_reverse_array()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, -5, 8, 2};
    int arr3[] = {1, 2, 3};

    int expected_arr1[] = {5, 4, 3, 2, 1};
    int expected_arr2[] = {2, 8, -5, 10};
    int expected_arr3[] = {3, 2, 1};

    // Test with arr1
    reverse_array(arr1, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected_arr1, arr1, 5, "Input: {1, 2, 3, 4, 5}");

    // Test with arr2
    reverse_array(arr2, 4);
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected_arr2, arr2, 4, "Input: {10, -5, 8, 2}");

    // Test with arr3
    reverse_array(arr3, 3);
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected_arr3, arr3, 3, "Input: {1, 2, 3}");
}

void test_is_prime()
{
    // Test with a prime number (17)
    TEST_ASSERT_EQUAL_MESSAGE(true, is_prime(17), "Input: 17");

    // Test with a non-prime number (10)
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(10), "Input: 10");

    // Test with a negative integer (-5)
    TEST_ASSERT_EQUAL_MESSAGE(false, is_prime(-5), "Input: -5");
}

void test_find_max_element()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, -5, 8, 2};
    int arr3[] = {0, 0, 0, 0, 0};

    // Test with arr1
    TEST_ASSERT_EQUAL_MESSAGE(5, find_max_element(arr1, 5), "Input: {1, 2, 3, 4, 5}");

    // Test with arr2
    TEST_ASSERT_EQUAL_MESSAGE(10, find_max_element(arr2, 4), "Input: {10, -5, 8, 2}");

    // Test with arr3 (all zeros)
    TEST_ASSERT_EQUAL_MESSAGE(0, find_max_element(arr3, 5), "Input: {0, 0, 0, 0, 0}");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_replace_even_with_8);
    RUN_TEST(test_reverse_array);
    RUN_TEST(test_is_prime);
    RUN_TEST(test_find_max_element);
    return UNITY_END();
}
