#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num1;
    int num2;

    // Ask the user to input two numbers
    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    bool greater = num1 > num2;
    bool smaller = num1 < num2;
    bool equality = num1 == num2;
    bool inequality = num1 != num2;

    printf("Num1 is greater than num2? %d\n", greater);
    printf("Num1 is smaller than num2?: %d\n", smaller);
    printf("Num1 is equal to num2?: %d\n", equality);
    printf("Num1 is different from num2?: %d\n", inequality);

    return 0;
}
