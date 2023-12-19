#include <stdbool.h>
#include "unity/unity.h"

#include "../simple.c"

void setUp() {}

void tearDown() {}

void test_sum_of_string_lengths()
{
    TEST_ASSERT_EQUAL_MESSAGE(10, sum_of_string_lengths("Hello", "World"), "Input: 'Hello', 'World'");
    TEST_ASSERT_EQUAL_MESSAGE(0, sum_of_string_lengths("", ""), "Input: '', '' (empty strings)");
    TEST_ASSERT_EQUAL_MESSAGE(12, sum_of_string_lengths("Apple", "and Cat"), "Input: 'Apple', 'and Cat'");
}

void test_are_three_strings_equal()
{
    TEST_ASSERT_TRUE_MESSAGE(are_three_strings_equal("apple", "apple", "apple"), "Input: 'apple', 'apple', 'apple'");
    TEST_ASSERT_FALSE_MESSAGE(are_three_strings_equal("apple", "banana", "apple"), "Input: 'apple', 'banana', 'apple'");
    TEST_ASSERT_FALSE_MESSAGE(are_three_strings_equal("cat", "cat", "dog"), "Input: 'cat', 'cat', 'dog'");
}

void test_concatenate_three_strings()
{
    char dest[20] = "Hello, ";
    char *result = concatenate_three_strings(dest, "World", "!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, World!", result, "Concatenation result is incorrect");
}

void test_find_longest_string()
{
    char *strings1[] = {"apple", "banana", "cherry"};
    char *result1 = find_longest_string(strings1, 3);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("banana", result1, "Input: {'apple', 'banana', 'cherry'}");

    char *strings2[] = {"cat", "dog", "elephant", "giraffe"};
    char *result2 = find_longest_string(strings2, 4);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("elephant", result2, "Input: {'cat', 'dog', 'elephant', 'giraffe'}");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_sum_of_string_lengths);
    RUN_TEST(test_are_three_strings_equal);
    RUN_TEST(test_concatenate_three_strings);
    RUN_TEST(test_find_longest_string);
    return UNITY_END();
}
