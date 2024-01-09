#include <stdbool.h>
#include "unity/unity.h"

#include "../advanced.c"

void setUp() {}

void tearDown() {}

void test_max_age()
{
    student_t students[] = {{20, 160.0}, {22, 175.0}, {18, 150.0}, {21, 180.0}};
    TEST_ASSERT_EQUAL_INT_MESSAGE(22, max_age(students, 4), "Max age calculation is incorrect");

    student_t students2[] = {{25, 160.0}, {25, 175.0}, {25, 150.0}, {25, 180.0}};
    TEST_ASSERT_EQUAL_INT_MESSAGE(25, max_age(students2, 4), "Max age calculation is incorrect for equal ages");
}

void test_are_points_equal()
{
    point_t points1[] = {{1, 2}, {1, 2}, {1, 2}};
    TEST_ASSERT_TRUE_MESSAGE(are_points_equal(points1, 3), "All points {1, 2} should be equal but the function returned false");

    point_t points2[] = {{1, 2}, {3, 4}, {5, 6}};
    TEST_ASSERT_FALSE_MESSAGE(are_points_equal(points2, 3), "Points {1, 2} and {3, 4} should not be equal but the function returned true");
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_max_age);
    RUN_TEST(test_are_points_equal);

    return UNITY_END();
}
