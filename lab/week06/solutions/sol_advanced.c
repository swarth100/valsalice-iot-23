#include <stdio.h>
#include <stdbool.h>

// Function to double the values in an array
void doubleArrayValues(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] *= 2;
    }
}

// Function to check if an array contains a number
bool containsNumber(int arr[], int size, int number)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == number)
        {
            return true;
        }
    }
    return false;
}

// Function to sum the elements of an array
int sumArray(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

/***********************************************************************************/
// DO NOT EDIT! Main function for demonstration
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int testArr1[5];
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
