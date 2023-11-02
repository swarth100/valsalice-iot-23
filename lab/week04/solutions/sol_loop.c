#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num;
    printf("Input a number greater than 100: ");
    scanf("%d", &num);

    while (num <= 100)
    {
        printf("Wrong number, try again: ");
        scanf("%d", &num);
    }

    printf("Well done!\n");

    return 0;
}
