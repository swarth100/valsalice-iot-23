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
    int max = students[0].age;
    for (int i = 1; i < num_students; i++)
    {
        if (students[i].age > max)
        {
            max = students[i].age;
        }
    }
    return max;
}

// Exercise 2: Implement a function are_points_equal that returns true if all points have the same x and y
typedef struct
{
    int x;
    int y;
} point_t;

bool are_points_equal(point_t points[], size_t num_points)
{
    int first_x = points[0].x;
    int first_y = points[0].y;

    for (int i = 1; i < num_points; i++)
    {
        if (points[i].x != first_x || points[i].y != first_y)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    printf("You should use 'make advanced.test' for this exercise!");
    return 1;
}