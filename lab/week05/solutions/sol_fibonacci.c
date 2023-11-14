#include <stdio.h>
#include <stdlib.h>

// Fibonacci function
int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main(int argc, char *argv[])
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("Fibonacci(%d) = %d\n", num, fibonacci(num));
    return 0;
}
#endif
