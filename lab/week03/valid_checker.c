#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num;

    // Ask the user to input one number:
    printf("Enter a number: ");
    scanf("%d", &num);

    // Validity Check:
    bool is_valid = (num >= 0) && (num <= 100);

    printf("Is the number valid? %d\n", is_valid);

    return 0;
}
