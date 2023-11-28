#include <stdio.h>
#include <stdbool.h>

// Function to get the second element of an array
int getSecondElement(int arr[])
{
    return arr[1];
}

// Function to get the last element of an array
int getLastElement(int arr[], int size)
{
    return arr[size - 1];
}

/***********************************************************************************/
// DO NOT EDIT! Main function for demonstration
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int testArr1[5];
    int testArr2[5] = {1, 2, 3, 4, 5};

    printf("Second element of the array: %d\n", getSecondElement(testArr2));
    printf("Last element of the array: %d\n", getLastElement(testArr2, 5));

    return 0;
}
#endif
