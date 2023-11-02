#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num;

    // Ask the user to input one number:
    printf("Insert a number: ");
    scanf("%d", &num);

    // Implementation:
    if (num < 0)
    {
        printf("NEGATIVE\n");
    }
    else if (num > 0)
    {
        printf("POSITIVE\n");
    }
    else
    {
        printf("ZERO\n");
    }

    return 0;
}
