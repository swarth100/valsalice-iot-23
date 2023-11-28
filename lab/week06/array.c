#include <stdio.h>
#include <stdbool.h>

// Function to add value `8` five times to `arr`
void createArrayAllEights(int arr[])
{
    // TODO: Implement!
    for (_____)
    {
        arr[_____] = _____
    }
}

// Function to add values `1` to `5` to `arr`
void createArrayOneToFive(int arr[])
{
    // TODO: Implement!
    // HINT: Use a for-loop!
}

/***********************************************************************************/
// DO NOT EDIT! Main function for demonstration
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int testArr1[5] = {0, 0, 0, 0, 0};

    createArrayAllEights(testArr1);
    printf("Array of all 8s: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", testArr1[i]);
    }
    printf("\n");

    createArrayOneToFive(testArr1);
    printf("Array from 1 to 5: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", testArr1[i]);
    }
    printf("\n");

    return 0;
}
#endif
