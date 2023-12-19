#include <stdbool.h>
#include "unity/unity.h"

#include "../advanced.c"

void setUp() {}

void tearDown() {}

void test_count_char_occurrences()
{
    TEST_ASSERT_EQUAL_MESSAGE(2, count_char_occurrences("programming", 'g'), "Input: 'programming', 'g'");
    TEST_ASSERT_EQUAL_MESSAGE(2, count_char_occurrences("hello", 'l'), "Input: 'hello', 'l'");
    TEST_ASSERT_EQUAL_MESSAGE(0, count_char_occurrences("world", 'z'), "Input: 'world', 'z'");
}

void test_convert_to_lowercase()
{
    char str[] = "LoWeRCaSe";
    char *result = convert_to_lowercase(str);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("lowercase", result, "Conversion to lowercase is incorrect");
}

void test_reverse_string()
{
    char str1[] = "hello";
    reverse_string(str1);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("olleh", str1, "Reversed string is incorrect for 'hello'");

    char str2[] = "world";
    reverse_string(str2);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("dlrow", str2, "Reversed string is incorrect for 'world'");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_count_char_occurrences);
    RUN_TEST(test_convert_to_lowercase);
    RUN_TEST(test_reverse_string);
    return UNITY_END();
}
