#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num;

    // Ask the user to input one number:
    printf("Insert a number: ");
    scanf("%d", &num);

    // Implementation:
    if (num % 2 == 0)
    {
        printf("Fizz");
    }
    if (num % 3 == 0)
    {
        printf("Buzz");
    }
    printf("\n");

    return 0;
}
