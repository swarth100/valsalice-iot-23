#include <stdbool.h>
#include "unity/unity.h"

#include "../simple.c"

void setUp() {}

void tearDown() {}

void test_student_struct_definition()
{
    student_t student;
    // Test if the student_t struct is defined correctly with correct field names
    TEST_ASSERT_TRUE_MESSAGE(sizeof(student) == sizeof(int) * 2, "Student struct size is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(student.height) == sizeof(int), "Student height field is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(student.age) == sizeof(int), "Student age field is incorrect");
}

void test_point_struct_definition()
{
    point_t point;
    // Test if the point_t struct is defined correctly with correct field names
    TEST_ASSERT_TRUE_MESSAGE(sizeof(point) == sizeof(int) * 2, "Point struct size is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(point.x) == sizeof(int), "Point x field is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(point.y) == sizeof(int), "Point y field is incorrect");
}

void test_prism_struct_definition()
{
    prism_t prism;
    // Test if the prism_t struct is defined correctly with correct field names
    TEST_ASSERT_TRUE_MESSAGE(sizeof(prism) == sizeof(float) * 3, "Prism struct size is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(prism.width) == sizeof(float), "Prism width field is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(prism.height) == sizeof(float), "Prism height field is incorrect");
    TEST_ASSERT_TRUE_MESSAGE(sizeof(prism.depth) == sizeof(float), "Prism depth field is incorrect");
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_student_struct_definition);
    RUN_TEST(test_point_struct_definition);
    RUN_TEST(test_prism_struct_definition);

    return UNITY_END();
}
