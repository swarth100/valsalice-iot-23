#include <stdio.h>
#include <stdbool.h>

// Function to calculate the next even number
int next_even(int num)
{
    // TODO: CHANGE RETURN!
    // HINT: Use an if-statement
    return 0;
}

// Function to calculate the factorial of a non-negative integer
int factorial(int num)
{
    // TODO: CHANGE RETURN!
    // HINT: Use a loop (or recursion)
    return 0;
}

// Calculate the sum of all natural numbers from 1 to n
int sum_of_natural_numbers(int num)
{
    // TODO: CHANGE RETURN!
    // HINT: Use a loop (or recursion)
    return 0;
}

// Function to check if a number is a prime number
bool is_prime(int num)
{
    // TODO: CHANGE RETURN!
    // HINT: Use a loop
    return false;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("Next even number: %d\n", next_even(num));
    printf("Factorial: %d\n", factorial(num));
    printf("Sum of natural numbers: %d\n", sum_of_natural_numbers(num));

    if (is_prime(num))
    {
        printf("%d is a prime number.\n", num);
    }
    else
    {
        printf("%d is not a prime number.\n", num);
    }

    return 0;
}
#endif
