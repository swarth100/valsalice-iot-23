#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define the User struct
typedef struct person
{
    int age;
    float height;
} person_t;

person_t create_person(int age, float height)
{
    person_t person = {age, height};
    return person;
}

int add_people_ages(person_t person1, person_t person2)
{
    return person1.age + person2.age;
}

bool is_person_1_taller_than_person_2(person_t person1, person_t person2)
{
    return person1.height > person2.height;
}

/***********************************************************************************/
// DO NOT EDIT! Main function
/***********************************************************************************/
#ifndef TESTING
int main()
{
    // Initialize variables for name, age, and height
    int age1;
    float height1;

    // Input data for the first person
    printf("Enter the age of the first person: ");
    scanf("%d", &age1);
    printf("Enter the height of the first person: ");
    scanf("%f", &height1);

    // Call create_person function to initialize the first person
    person_t person1 = create_person(age1, height1);

    // Initialize variables for name, age, and height
    int age2;
    float height2;

    // Input data for the second person
    printf("Enter the age of the second person: ");
    scanf("%d", &age2);
    printf("Enter the height of the second person: ");
    scanf("%f", &height2);

    // Call create_person function to initialize the second person
    person_t person2 = create_person(age2, height2);

    // Print information about the people
    printf("\nFirst Person:\n");
    printf("Age: %d\n", person1.age);
    printf("Height: %.2f\n", person1.height);

    printf("\nSecond Person:\n");
    printf("Age: %d\n", person2.age);
    printf("Height: %.2f\n", person2.height);

    // Calculate and print the sum of ages
    int sum_of_ages = add_people_ages(person1, person2);
    printf("\nSum of Ages: %d\n", sum_of_ages);

    // Check and print if the first person is taller than the second person
    bool is_taller = is_person_1_taller_than_person_2(person1, person2);
    printf("Is the first Person is taller than the Second person? %d.\n", is_taller);

    return 0;
}
#endif
