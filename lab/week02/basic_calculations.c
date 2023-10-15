#include <stdio.h>
#include <stdbool.h>

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
    return (float)num1 / num2;
}

// Function to compare two numbers and return true if num1 is greater than num2
bool greater_than(int num1, int num2) {
    return num1 > num2;
}

// Function to compare two numbers and return true if num1 is less than num2
bool less_than(int num1, int num2) {
    return num1 < num2;
}

// Function to compare two numbers and return true if num1 equals num2
bool equals(int num1, int num2) {
    return num1 == num2;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main() {
    int num1, num2;
    
    printf("Enter the first number: ");
    scanf("%d", &num1);
    
    printf("Enter the second number: ");
    scanf("%d", &num2);
    
    printf("Sum: %d\n", add(num1, num2));
    printf("Difference: %d\n", subtract(num1, num2));
    printf("Product: %d\n", multiply(num1, num2));
    
    if (num2 != 0) {
        printf("Division: %.2f\n", divide(num1, num2));
    } else {
        printf("Cannot perform division by 0!\n");
    }
    
    printf("Is the first number greater? %s\n", greater_than(num1, num2) ? "true" : "false");
    printf("Is the first number lower? %s\n", less_than(num1, num2) ? "true" : "false");
    printf("Are the numbers equal? %s\n", equals(num1, num2) ? "true" : "false");

    return 0;
}
#endif
