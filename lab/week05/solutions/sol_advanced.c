#include <stdio.h>
#include <stdbool.h>

// Function to calculate the next even number
int next_even(int num)
{
    if (num % 2 == 0)
    {
        // If the input is even, return the next even number.
        return num + 2;
    }
    else
    {
        // If the input is odd, return the next even number.
        return num + 1;
    }
}

// Function to calculate the factorial of a non-negative integer
int factorial(int num)
{
    // This exercise can also be solved with recursion
    int result = 1;
    for (int i = 1; i <= num; i++)
    {
        result *= i;
    }
    return result;
}

// Calculate the sum of all natural numbers from 1 to n
int sum_of_natural_numbers(int num)
{
    // This exercise cal also be solved with a loop
    if (num <= 0)
    {
        return num;
    }
    else
    {
        return num + sum_of_natural_numbers(num - 1);
    }
}

// Function to check if a number is a prime number
bool is_prime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
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
