#include "unity/unity.h"
#include "../family.c"

// Define setup and teardown functions if needed
void setUp(void)
{
    // Set up resources before each test
}

void tearDown(void)
{
    // Clean up resources after each test
}

// Test add_people_ages function
void test_add_people_ages(void)
{
    // Create two person_t structs for testing
    person_t person1 = create_person(30, 175.5);
    person_t person2 = create_person(25, 165.0);

    // Call the function to be tested
    int result = add_people_ages(person1, person2);

    // Use Unity's assertion functions to check the result
    TEST_ASSERT_EQUAL_INT(55, result); // Expected sum of ages
}

// Test is_person_1_taller_than_person_2 function (person1 taller)
void test_is_person_1_taller_than_person_2_taller(void)
{
    // Create two person_t structs for testing
    person_t person1 = create_person(30, 175.5);
    person_t person2 = create_person(25, 165.0);

    // Call the function to be tested
    int result = is_person_1_taller_than_person_2(person1, person2);

    // Use Unity's assertion functions to check the result
    TEST_ASSERT_EQUAL_INT(1, result); // Expecting person1 to be taller
}

// Test is_person_1_taller_than_person_2 function (person2 taller)
void test_is_person_1_taller_than_person_2_shorter(void)
{
    // Create two person_t structs for testing
    person_t person1 = create_person(25, 165.0);
    person_t person2 = create_person(30, 175.5);

    // Call the function to be tested
    int result = is_person_1_taller_than_person_2(person1, person2);

    // Use Unity's assertion functions to check the result
    TEST_ASSERT_EQUAL_INT(0, result); // Expecting person2 to be taller
}

// Test is_person_1_taller_than_person_2 function (equal height)
void test_is_person_1_taller_than_person_2_equal_height(void)
{
    // Create two person_t structs for testing with equal height
    person_t person1 = create_person(25, 175.0);
    person_t person2 = create_person(30, 175.0);

    // Call the function to be tested
    int result = is_person_1_taller_than_person_2(person1, person2);

    // Use Unity's assertion functions to check the result
    TEST_ASSERT_EQUAL_INT(0, result); // Expecting equal height
}

// Test create_person function
void test_create_person(void)
{
    // Call the function to be tested to create a person
    person_t person = create_person(30, 175.5);

    // Use Unity's assertion functions to check the created person's attributes
    TEST_ASSERT_EQUAL_INT(30, person.age);                // Check age
    TEST_ASSERT_FLOAT_WITHIN(0.01, 175.5, person.height); // Check height with a tolerance
}

// Test create_person function with different values
void test_create_person_different_values(void)
{
    // Call the function to be tested to create a person
    person_t person = create_person(25, 160.0);

    // Use Unity's assertion functions to check the created person's attributes
    TEST_ASSERT_EQUAL_INT(25, person.age);                // Check age
    TEST_ASSERT_FLOAT_WITHIN(0.01, 160.0, person.height); // Check height with a tolerance
}

int main(void)
{
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_create_person);
    RUN_TEST(test_create_person_different_values);
    RUN_TEST(test_add_people_ages);
    RUN_TEST(test_is_person_1_taller_than_person_2_taller);
    RUN_TEST(test_is_person_1_taller_than_person_2_shorter);
    RUN_TEST(test_is_person_1_taller_than_person_2_equal_height);

    return UNITY_END();
}
