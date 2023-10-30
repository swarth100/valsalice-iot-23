#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num;

    // Ask the user to input one number:
    printf("Enter a number between 0 and 100: ");
    scanf("%d", &num);

    // Validity Check:
    if ((num >= 0) && (num <= 100))
    {
        printf("Well Done!\n");
    }
    else
    {
        printf("ERROR! Try again: ");
        scanf("%d", &num);
        printf("Well Done!\n");
    }

    return 0;
}
