#include <stdbool.h>
#include "unity/unity.h"

#include "../algebra.c"

void setUp() {}

void tearDown() {}

void test_add()
{
    TEST_ASSERT_EQUAL_MESSAGE(5, add(2, 3), "Input: 2, 3");
    TEST_ASSERT_EQUAL_MESSAGE(-1, add(2, -3), "Input: 2, -3");
    TEST_ASSERT_EQUAL_MESSAGE(0, add(0, 0), "Input: 0, 0");
}

void test_subtract()
{
    TEST_ASSERT_EQUAL_MESSAGE(2, subtract(5, 3), "Input: 5, 3");
    TEST_ASSERT_EQUAL_MESSAGE(5, subtract(2, -3), "Input: 2, -3");
    TEST_ASSERT_EQUAL_MESSAGE(0, subtract(0, 0), "Input: 0, 0");
}

void test_multiply()
{
    TEST_ASSERT_EQUAL_MESSAGE(6, multiply(2, 3), "Input: 2, 3");
    TEST_ASSERT_EQUAL_MESSAGE(-6, multiply(2, -3), "Input: 2, -3");
    TEST_ASSERT_EQUAL_MESSAGE(0, multiply(0, 0), "Input: 0, 0");
}

void test_divide()
{
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.0, divide(6, 3), "Input: 6, 3");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-2.0, divide(-6, 3), "Input: -6, 3");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.0, divide(0, 5), "Input: 0, 5");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(1.5, divide(6, 4), "Input: 6, 4");
}

void test_greater_than()
{
    TEST_ASSERT_EQUAL_MESSAGE(true, greater_than(5, 3), "Input: 5, 3");
    TEST_ASSERT_EQUAL_MESSAGE(false, greater_than(2, 7), "Input: 2, 7");
    TEST_ASSERT_EQUAL_MESSAGE(false, greater_than(4, 4), "Input: 4, 4");
}

void test_less_than()
{
    TEST_ASSERT_EQUAL_MESSAGE(false, less_than(5, 3), "Input: 5, 3");
    TEST_ASSERT_EQUAL_MESSAGE(true, less_than(2, 7), "Input: 2, 7");
    TEST_ASSERT_EQUAL_MESSAGE(false, less_than(4, 4), "Input: 4, 4");
}

void test_equals()
{
    TEST_ASSERT_EQUAL_MESSAGE(false, equals(5, 3), "Input: 5, 3");
    TEST_ASSERT_EQUAL_MESSAGE(false, equals(2, 7), "Input: 2, 7");
    TEST_ASSERT_EQUAL_MESSAGE(true, equals(4, 4), "Input: 4, 4");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_add);
    RUN_TEST(test_subtract);
    RUN_TEST(test_multiply);
    RUN_TEST(test_divide);
    RUN_TEST(test_greater_than);
    RUN_TEST(test_less_than);
    RUN_TEST(test_equals);
    return UNITY_END();
}
