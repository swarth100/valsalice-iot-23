#include <stdio.h>

// Struct to hold operation and numbers
struct Calculation {
    char op;
    int num1;
    int num2;
};

// Function to perform calculation based on struct input
int performCalculation(struct Calculation calc) {
    switch (calc.op) {
        case '+':
            return calc.num1 + calc.num2;
        case '-':
            return calc.num1 - calc.num2;
        case '*':
            return calc.num1 * calc.num2;
        case '/':
            if (calc.num2 == 0) {
                printf("Error: Division by zero!\n");
                return 0;
            }
            return calc.num1 / calc.num2;
        default:
            printf("Error: Invalid operation '%c'\n", calc.op);
            return 0;
    }
}

int main() {
    struct Calculation calc;

    printf("Enter an arithmetic operation (+, -, *, /): ");
    scanf(" %c", &calc.op); // Note the space before %c to consume any leading whitespace

    printf("Enter the first number: ");
    scanf("%d", &calc.num1);

    printf("Enter the second number: ");
    scanf("%d", &calc.num2);

    int result = performCalculation(calc);

    printf("Result of %d %c %d is: %d\n", calc.num1, calc.op, calc.num2, result);

    return 0;
}
