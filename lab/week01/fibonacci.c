#include <stdio.h>
#include <stdlib.h>

// Fibonacci function
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Main function
#ifndef TESTING
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
    return 0;
}
#endif