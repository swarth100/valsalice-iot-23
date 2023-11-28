#include <stdbool.h>
#include "unity/unity.h"

#include "../simple.c"

void setUp() {}

void tearDown() {}

void test_getSecondElement(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_MESSAGE(2, getSecondElement(arr), "Input array: {1, 2, 3, 4, 5}");
    int arr2[] = {8, 13, 45, 23, 12};
    TEST_ASSERT_EQUAL_MESSAGE(13, getSecondElement(arr2), "Input array: {8, 13, 45, 23, 12}");
}

void test_getLastElement(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_MESSAGE(5, getLastElement(arr, 5), "Input array: {1, 2, 3, 4, 5}");
    int arr2[] = {8, 13, 45, 23, 12, 8, 9};
    TEST_ASSERT_EQUAL_MESSAGE(9, getLastElement(arr2, 7), "Input array: {8, 13, 45, 23, 12, 8, 9}");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getSecondElement);
    RUN_TEST(test_getLastElement);
    return UNITY_END();
}
