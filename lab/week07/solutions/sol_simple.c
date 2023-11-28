#include <stdio.h>

// Function to find the maximum of two numbers
int find_max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Function to calculate the sum of integers from 1 to n
int calculate_sum(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

// Function to find the sum of elements in an integer array
int array_sum(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

#ifndef TESTING
int main()
{
    int choice;

    printf("Select an option:\n");
    printf("1. Find the maximum of two numbers\n");
    printf("2. Calculate the sum of integers from 1 to n\n");
    printf("3. Find the sum of elements in an integer array\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int num1, num2;
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
        int max = find_max(num1, num2);
        printf("The maximum number is: %d\n", max);
    }
    else if (choice == 2)
    {
        int num;
        printf("Enter a positive integer: ");
        scanf("%d", &num);
        int sum = calculate_sum(num);
        printf("The sum of integers from 1 to %d is: %d\n", num, sum);
    }
    else if (choice == 3)
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
        int sum = array_sum(arr, size);
        printf("The sum of the elements in the array is: %d\n", sum);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
#endif
