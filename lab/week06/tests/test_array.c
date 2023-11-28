#include <stdbool.h>
#include "unity/unity.h"

#include "../array.c"

void setUp() {}

void tearDown() {}

void test_createArrayAllEights(void)
{
    int arr[5] = {0, 0, 0, 0, 0};
    createArrayAllEights(arr);
    for (int i = 0; i < 5; i++)
    {
        char msg[50];
        sprintf(msg, "Element at index %d should be 8, but was %d", i, arr[i]);
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
        sprintf(msg, "Element at index %d should be %d, but was %d", i, i + 1, arr[i]);
        TEST_ASSERT_EQUAL_MESSAGE(i + 1, arr[i], msg);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_createArrayAllEights);
    RUN_TEST(test_createArrayOneToFive);
    return UNITY_END();
}
