#include <stdio.h>
#include <stdbool.h>

// Function to replace integers at even indices with 8
// Example input: {1, 2, 3, 4, 5}
// Example output: {8, 2, 8, 4, 8}
void replace_even_with_8(int arr[], int size)
{
    // TODO: Implement this function
}

// Function to reverse an integer array
// Example input: {1, 2, 3, 4, 5}
// Example output: {5, 4, 3, 2, 1}
void reverse_array(int arr[], int size)
{
    // TODO: Implement this function
}

// Function to check if a number is prime
// Example input: 7
// Example output: true
// Example input: 12
// Example output: false
bool is_prime(int num)
{
    // TODO: Implement this function
    return false;
}

// Function to find the maximum element in an integer array
// Example input: {1, 7, 9, 4, 5}
// Example output: 9
int find_max_element(int arr[], int size)
{
    // TODO: Implement this function
    return -1;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    int choice;

    printf("Select an option:\n");
    printf("1. Replace integers at even indices with 8 in an array\n");
    printf("2. Reverse an integer array\n");
    printf("3. Check if a number is prime\n");
    printf("4. Find the maximum element in an integer array\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int size;

        printf("Enter the size of the array: ");
        scanf("%d", &size);

        int arr[size];

        printf("Enter %d integers:\n", size);
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &arr[i]);
        }

        replace_even_with_8(arr, size);

        printf("Modified Array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else if (choice == 2)
    {
        int size;

        printf("Enter the size of the array: ");
        scanf("%d", &size);

        int arr[size];

        printf("Enter %d integers:\n", size);
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &arr[i]);
        }

        reverse_array(arr, size);

        printf("Reversed Array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else if (choice == 3)
    {
        int num;

        printf("Enter an integer: ");
        scanf("%d", &num);

        if (is_prime(num))
        {
            printf("%d is a prime number.\n", num);
        }
        else
        {
            printf("%d is not a prime number.\n", num);
        }
    }
    else if (choice == 4)
    {
        int size;

        printf("Enter the size of the array: ");
        scanf("%d", &size);

        int arr[size];

        printf("Enter %d integers:\n", size);
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &arr[i]);
        }

        int max = find_max_element(arr, size);
        printf("The maximum element in the array is: %d\n", max);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
#endif