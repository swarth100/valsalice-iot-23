#include <stdio.h>
#include <stdbool.h>

// Function to create an array of all 8s
void createArrayAllEights(int arr[])
{
    for (int i = 0; i < 5; i++)
    {
        arr[i] = 8;
    }
}

// Function to create an array from 1 to 5
void createArrayOneToFive(int arr[])
{
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i + 1;
    }
}

/***********************************************************************************/
// DO NOT EDIT! Main function for demonstration
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int testArr1[5];

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
