#include <stdio.h>

// Define a new struct point_t representing a point in 2D space
typedef struct
{
    int x;
    int y;
} point_t;

// Define a new struct rectangle_t that has two fields left and right both of type point_t
typedef struct
{
    point_t left;
    point_t right;
} rectangle_t;

// Implement a function find_area that given a rectangle_t struct, returns the area of the rectangle
int find_area(rectangle_t rect)
{
    int width = rect.right.x - rect.left.x;
    int height = rect.right.y - rect.left.y;
    return width * height;
}

int main()
{
    printf("You should use 'make nested.test' for this exercise!");
    return 1;
}
