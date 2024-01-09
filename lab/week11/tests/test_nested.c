#include <stdbool.h>
#include "unity/unity.h"

#include "../nested.c"

void setUp() {}

void tearDown() {}

void test_rectangle_t_struct()
{
    rectangle_t rect = {{1, 2}, {3, 4}};

    TEST_ASSERT_EQUAL_INT_MESSAGE(1, rect.left.x, "Left point x-coordinate is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, rect.left.y, "Left point y-coordinate is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, rect.right.x, "Right point x-coordinate is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, rect.right.y, "Right point y-coordinate is incorrect");
}

void test_find_area()
{
    rectangle_t rect1 = {{1, 1}, {4, 4}}; // Rectangle with sides 3x3
    TEST_ASSERT_EQUAL_INT_MESSAGE(9, find_area(rect1), "Area calculation is incorrect for rect1");

    rectangle_t rect2 = {{0, 0}, {5, 5}}; // Rectangle with sides 5x5
    TEST_ASSERT_EQUAL_INT_MESSAGE(25, find_area(rect2), "Area calculation is incorrect for rect2");

    rectangle_t rect3 = {{-2, -2}, {2, 2}}; // Rectangle with sides 4x4
    TEST_ASSERT_EQUAL_INT_MESSAGE(16, find_area(rect3), "Area calculation is incorrect for rect3");
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_rectangle_t_struct);
    RUN_TEST(test_find_area);

    return UNITY_END();
}
