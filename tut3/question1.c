#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int age;
    char* firstName[32];
    float height;

    printf("Input your first name: ");
    fgets(&firstName, 32, stdin);
    printf("Input your age: ");
    scanf("%d\n", age);
    printf("Input your height: ");
    scanf("%f\n", height);

    printf("Your name is %s\nYour age is %d\nYour height is %f", firstName, age, height);
}
