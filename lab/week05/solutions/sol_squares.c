#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num;

    // Ask the user to input one number:
    printf("Insert a number: ");
    scanf("%d", &num);

    /* ******************************************* *
     * TODO: Implement operations BELOW this line! *
     * ******************************************* */

    for (int x = 1; x <= num; x++)
    {
        printf("%d\n", x * x);
    }

    /* ******************************************* *
     * TODO: Implement operations ABOVE this line! *
     * ******************************************* */

    return 0;
}
