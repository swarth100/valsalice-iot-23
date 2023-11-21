#include <stdio.h>
#include <stdbool.h>

// Function to calculate 3x + 2y - z
float calculate_expression(float x, float y, float z)
{
    // TODO: REPLACE with implementation!
    return -1;
}

// Function to return 2x if x is even, otherwise -x
int double_or_negate(int x)
{
    // TODO: REPLACE with implementation!
    return -1;
}

// Function to return sum if it's less than 100, otherwise the smallest number
int sum_or_min(int x, int y)
{
    // TODO: REPLACE with implementation!
    return -1;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    float x, y, z;
    int num;

    // Test for calculate_expression
    printf("Enter three numbers (x, y, z) for 3x + 2y - z: ");
    scanf("%f %f %f", &x, &y, &z);
    printf("Result: %.2f\n", calculate_expression(x, y, z));

    // Test for double_or_negate
    printf("Enter a number to double if even or negate if odd: ");
    scanf("%d", &num);
    printf("Result: %d\n", double_or_negate(num));

    // Test for sum_or_min
    printf("Enter two numbers to sum (or find the minimum if sum >= 100): ");
    scanf("%f %f", &x, &y);
    printf("Result: %d\n", sum_or_min(x, y));

    return 0;
}
#endif
