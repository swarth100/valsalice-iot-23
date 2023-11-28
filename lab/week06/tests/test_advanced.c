#include <stdbool.h>
#include "unity/unity.h"

#include "../advanced.c"

void setUp() {}

void tearDown() {}

void test_doubleArrayValues(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    doubleArrayValues(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        char msg[50];
        sprintf(msg, "Element at index %d should be %d, but was %d", i, (i + 1) * 2, arr[i]);
        TEST_ASSERT_EQUAL_MESSAGE((i + 1) * 2, arr[i], msg);
    }
}

void test_containsNumber(void)
{
    int arr[] = {2, 4, 6, 8, 10};
    TEST_ASSERT_TRUE_MESSAGE(containsNumber(arr, 5, 4), "Array {2, 4, 6, 8, 10} should contain 4");
    TEST_ASSERT_FALSE_MESSAGE(containsNumber(arr, 5, 3), "Array {2, 4, 6, 8, 10} should not contain 3");
}

void test_sumArray(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_MESSAGE(15, sumArray(arr, 5), "Sum of array {1, 2, 3, 4, 5} elements should be 15");
    int smallArr[] = {2};
    TEST_ASSERT_EQUAL_MESSAGE(2, sumArray(smallArr, 1), "Sum of array {2} should be 2");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_doubleArrayValues);
    RUN_TEST(test_containsNumber);
    RUN_TEST(test_sumArray);
    return UNITY_END();
}
