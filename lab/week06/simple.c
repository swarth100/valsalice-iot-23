#include <stdio.h>
#include <stdbool.h>

// Function to get the second element of an array
int getSecondElement(int arr[])
{
    // TODO: REPLACE with implementation!
    return arr[_____];
}

// Function to get the last element of an array
int getLastElement(int arr[], int size)
{
    // TODO: REPLACE with implementation!
    return _____;
}

/***********************************************************************************/
// DO NOT EDIT! Main function for demonstration
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int testArr1[5] = {0, 0, 0, 0, 0};
    int testArr2[5] = {1, 2, 3, 4, 5};

    printf("Second element of the array: %d\n", getSecondElement(testArr2));
    printf("Last element of the array: %d\n", getLastElement(testArr2, 5));

    return 0;
}
#endif
