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

    // Perform the operations
    int sum = num1 + num2;
    int difference = num1 - num2;
    int multiplication = num1 * num2;
    int division = num1 / num2;

    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);
    printf("Multiplication: %d\n", multiplication);
    printf("Division: %d\n", division);

    return 0;
}
