#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

size_t sum_of_string_lengths(char *str1, char *str2)
{
    return strlen(str1) + strlen(str2);
}

bool are_three_strings_equal(char *str1, char *str2, char *str3)
{
    return (strcmp(str1, str2) == 0) && (strcmp(str2, str3) == 0);
}

char *concatenate_three_strings(char *dest, char *src1, char *src2)
{
    strcat(dest, src1);
    strcat(dest, src2);
    return dest;
}

char *find_longest_string(char *strings[], size_t num_strings)
{
    size_t max_length = 0;
    char *longest_string = NULL;

    for (size_t i = 0; i < num_strings; i++)
    {
        size_t length = strlen(strings[i]);
        if (length > max_length)
        {
            max_length = length;
            longest_string = strings[i];
        }
    }
    return longest_string;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    printf("You should use 'make string.test' for this exercise!");
    return 1;
}
#endif