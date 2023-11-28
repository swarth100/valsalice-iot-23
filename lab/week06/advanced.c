#include <stdio.h>
#include <stdbool.h>

// Function to double the values in `arr`
void doubleArrayValues(int arr[], int size)
{
    // TODO: Implement!
}

// Function to check if `arr` contains a specific number
bool containsNumber(int arr[], int size, int number)
{
    // TODO: REPLACE with implementation!
    return false;
}

// Function to sum the elements of `arr`
int sumArray(int arr[], int size)
{
    // TODO: REPLACE with implementation!
    return -1;
}

/***********************************************************************************/
// DO NOT EDIT! Main function for demonstration
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int testArr1[5] = {0, 0, 0, 0, 0};
    int testArr2[5] = {1, 2, 3, 4, 5};

    doubleArrayValues(testArr2, 5);
    printf("Doubled array values: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", testArr2[i]);
    }
    printf("\n");

    printf("Does array contain number 4? %s\n", containsNumber(testArr2, 5, 4) ? "Yes" : "No");
    printf("Sum of array elements: %d\n", sumArray(testArr2, 5));

    return 0;
}
#endif
