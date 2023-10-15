#include <stdio.h>

// Function to add two numbers
int add(int num1, int num2) {
    return num1 + num2;
}

// Function to subtract two numbers
int subtract(int num1, int num2) {
    return num1 - num2;
}

// Function to multiply two numbers
int multiply(int num1, int num2) {
    return num1 * num2;
}

// Function to divide two numbers
float divide(int num1, int num2) {
    if (num2 == 0) {
        printf("Error: Division by zero!\n");
        return 0.0;
    }
    return (float)num1 / num2;
}

// Function to compare two numbers and return 1 if num1 is greater, 0 if equal, and -1 if num2 is greater
int compare(int num1, int num2) {
    if (num1 > num2) {
        return 1;
    } else if (num1 < num2) {
        return -1;
    } else {
        return 0;
    }
}

int main() {
    int num1, num2;
    
    printf("Enter the first number: ");
    scanf("%d", &num1);
    
    printf("Enter the second number: ");
    scanf("%d", &num2);
    
    printf("Sum: %d\n", add(num1, num2));
    printf("Difference: %d\n", subtract(num1, num2));
    printf("Product: %d\n", multiply(num1, num2));
    
    float result = divide(num1, num2);
    if (result != 0.0) {
        printf("Division: %.2f\n", result);
    }
    
    int comparison = compare(num1, num2);
    if (comparison == 1) {
        printf("%d is greater than %d\n", num1, num2);
    } else if (comparison == -1) {
        printf("%d is greater than %d\n", num2, num1);
    } else {
        printf("Both numbers are equal\n");
    }
    
    return 0;
}
