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

    printf("Second element of the array: %d\n", getSecondElement(testArr2));
    printf("Last element of the array: %d\n", getLastElement(testArr2, 5));

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
