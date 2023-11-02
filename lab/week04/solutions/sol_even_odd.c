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
        printf("EVEN\n");
    }
    else
    {
        printf("ODD\n");
    }

    return 0;
}
