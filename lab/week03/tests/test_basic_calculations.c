#include <stdbool.h>
#include "unity/unity.h"

#include "../basic_calculations.c"

void setUp() {}

void tearDown() {}

void test_add() {
    TEST_ASSERT_EQUAL(5, add(2, 3));
    TEST_ASSERT_EQUAL(-1, add(2, -3));
    TEST_ASSERT_EQUAL(0, add(0, 0));
}

void test_subtract() {
    TEST_ASSERT_EQUAL(2, subtract(5, 3));
    TEST_ASSERT_EQUAL(5, subtract(2, -3));
    TEST_ASSERT_EQUAL(0, subtract(0, 0));
}

void test_multiply() {
    TEST_ASSERT_EQUAL(6, multiply(2, 3));
    TEST_ASSERT_EQUAL(-6, multiply(2, -3));
    TEST_ASSERT_EQUAL(0, multiply(0, 0));
}

void test_divide() {
    TEST_ASSERT_EQUAL_FLOAT(2.0, divide(6, 3));
    TEST_ASSERT_EQUAL_FLOAT(-2.0, divide(-6, 3));
    TEST_ASSERT_EQUAL_FLOAT(0.0, divide(0, 5));
    TEST_ASSERT_EQUAL_FLOAT(1.5, divide(6, 4));
}

void test_greater_than() {
    TEST_ASSERT_EQUAL(true, greater_than(5, 3));
    TEST_ASSERT_EQUAL(false, greater_than(2, 7));
    TEST_ASSERT_EQUAL(false, greater_than(4, 4));
}

void test_less_than() {
    TEST_ASSERT_EQUAL(false, less_than(5, 3));
    TEST_ASSERT_EQUAL(true, less_than(2, 7));
    TEST_ASSERT_EQUAL(false, less_than(4, 4));
}

void test_equals() {
    TEST_ASSERT_EQUAL(false, equals(5, 3));
    TEST_ASSERT_EQUAL(false, equals(2, 7));
    TEST_ASSERT_EQUAL(true, equals(4, 4));
}

int main() {
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
