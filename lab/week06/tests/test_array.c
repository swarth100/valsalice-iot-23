#include <stdbool.h>
#include "unity/unity.h"

#include "../array.c"

void setUp() {}

void tearDown() {}

void test_getSecondElement(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL(2, getSecondElement(arr));
}

void test_getLastElement(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL(5, getLastElement(arr, 5));
}

void test_createArrayAllEights(void)
{
    int arr[5] = {0, 0, 0, 0, 0};
    createArrayAllEights(arr);
    for (int i = 0; i < 5; i++)
    {
        char msg[50];
        sprintf(msg, "Element %d should be 8, but was %d", i, arr[i]);
        TEST_ASSERT_EQUAL_MESSAGE(8, arr[i], msg);
    }
}

void test_createArrayOneToFive(void)
{
    int arr[5] = {0, 0, 0, 0, 0};
    createArrayOneToFive(arr);
    for (int i = 0; i < 5; i++)
    {
        char msg[50];
        sprintf(msg, "Element %d should be %d, but was %d", i, i + 1, arr[i]);
        TEST_ASSERT_EQUAL_MESSAGE(i + 1, arr[i], msg);
    }
}

void test_doubleArrayValues(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    doubleArrayValues(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        char msg[50];
        sprintf(msg, "Element %d should be %d, but was %d", i, (i + 1) * 2, arr[i]);
        TEST_ASSERT_EQUAL_MESSAGE((i + 1) * 2, arr[i], msg);
    }
}

void test_containsNumber(void)
{
    int arr[] = {2, 4, 6, 8, 10};
    TEST_ASSERT_TRUE_MESSAGE(containsNumber(arr, 5, 4), "Array should contain 4");
    TEST_ASSERT_FALSE_MESSAGE(containsNumber(arr, 5, 3), "Array should not contain 3");
}

void test_sumArray(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_MESSAGE(15, sumArray(arr, 5), "Sum of array elements should be 15");
    int smallArr[] = {2};
    TEST_ASSERT_EQUAL_MESSAGE(2, sumArray(smallArr, 1), "Sum of empty array should be 2");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getSecondElement);
    RUN_TEST(test_getLastElement);
    RUN_TEST(test_createArrayAllEights);
    RUN_TEST(test_createArrayOneToFive);
    RUN_TEST(test_doubleArrayValues);
    RUN_TEST(test_containsNumber);
    RUN_TEST(test_sumArray);
    return UNITY_END();
}
