#include <stdbool.h>
#include "unity/unity.h"

#include "../medium.c"

void setUp() {}

void tearDown() {}

void test_add_heights()
{
    student_t student1 = {20, 160.0};
    student_t student2 = {22, 175.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(335.0, add_heights(student1, student2), "Height addition is incorrect");
}

void test_create_point()
{
    point_t new_point = create_point(10, 20);
    TEST_ASSERT_EQUAL_INT_MESSAGE(10, new_point.x, "Point x value is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(20, new_point.y, "Point y value is incorrect");
}

void test_calculate_volume()
{
    prism_t prism = {5.0, 4.0, 3.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(60.0, calculate_volume(prism), "Volume calculation is incorrect");
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_add_heights);
    RUN_TEST(test_create_point);
    RUN_TEST(test_calculate_volume);

    return UNITY_END();
}
