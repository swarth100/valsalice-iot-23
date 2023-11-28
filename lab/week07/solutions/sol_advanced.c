#include <stdio.h>
#include <stdbool.h>

// Function to replace integers at even indices with 8
void replace_even_with_8(int arr[], int size)
{
    for (int i = 0; i < size; i += 2)
    {
        arr[i] = 8;
    }
}

// Function to reverse an integer array
void reverse_array(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

// Function to check if a number is prime
bool is_prime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

// Function to find the maximum element in an integer array
int find_max_element(int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
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
