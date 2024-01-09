#include <stdio.h>
#include <stdbool.h>

#include <stdio.h>

// Define a new struct point_t representing a point in 2D space
typedef struct
{
    int x;
    int y;
} point_t;

// Exercise 1: Define a new struct rectangle_t that has two fields left and right both of type point_t
// TODO: Implement

// Exercise 2: Implement a function find_area that given a rectangle_t struct, returns the area of the rectangle
int find_area(rectangle_t rect)
{
    // TODO: Implement the function to calculate the area of the rectangle
    return 0;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    printf("You should use 'make nested.test' for this exercise!");
    return 1;
}
#endif