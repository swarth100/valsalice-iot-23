#include <stdio.h>

// Exercise 1: Implement a function add_heights that returns the sum of heights
typedef struct
{
    int age;
    float height;
} student_t;

int add_heights(student_t first_student, student_t second_student)
{
    return first_student.height + second_student.height;
}

// Exercise 2: Implement a function create_point that returns a new point_t struct with the values set
typedef struct
{
    int x;
    int y;
} point_t;

point_t create_point(int x, int y)
{
    point_t new_point;
    new_point.x = x;
    new_point.y = y;
    return new_point;
}

// Exercise 3: Implement a function calculate_volume that returns the volume of a prism_t
typedef struct
{
    float width;
    float height;
    float depth;
} prism_t;

float calculate_volume(prism_t prism)
{
    return prism.width * prism.height * prism.depth;
}

int main()
{
    // You can add some code to test the functions here if needed
    return 0;
}
