#include "unity/unity.h"
#include "../enhanced_calculator.c"

void setUp() {}

void tearDown() {}

void test_performCalculation() {
    struct Calculation calc1 = {'+', 5, 3};
    struct Calculation calc2 = {'-', 5, 3};
    struct Calculation calc3 = {'*', 5, 3};
    struct Calculation calc4 = {'/', 6, 2};

    TEST_ASSERT_EQUAL(8, performCalculation(calc1));
    TEST_ASSERT_EQUAL(2, performCalculation(calc2));
    TEST_ASSERT_EQUAL(15, performCalculation(calc3));
    TEST_ASSERT_EQUAL(3, performCalculation(calc4));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_performCalculation);
    return UNITY_END();
}
