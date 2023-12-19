#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

size_t count_char_occurrences(char *str, char character)
{
    size_t count = 0;
    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] == character)
            count++;
    }
    return count;
}

char *convert_to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

void reverse_string(char *str)
{
    size_t length = strlen(str);
    for (size_t i = 0, j = length - 1; i < j; i++, j--)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
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