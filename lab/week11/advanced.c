#include <stdio.h>
#include <stdbool.h>

// Exercise 1: Implement a function max_age that returns the age of the oldest student
typedef struct
{
    int age;
    float height;
} student_t;

int max_age(student_t students[], size_t num_students)
{
    // TODO: Implement
    return 0;
}

// Exercise 2: Implement a function are_points_equal that returns true if all points have the same x and y
typedef struct
{
    int x;
    int y;
} point_t;

bool are_points_equal(point_t points[], size_t num_points)
{
    // TODO: Implement
    return false;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    printf("You should use 'make advanced.test' for this exercise!");
    return 1;
}
#endif