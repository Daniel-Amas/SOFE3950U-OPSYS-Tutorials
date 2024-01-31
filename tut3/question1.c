#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int age;
    char firstName[32];
    float height;

    printf("Input your first name: ");
    fgets(firstName, sizeof(firstName), stdin);

    printf("Input your age: ");
    scanf("%d", &age);
    
    printf("Input your height: ");
    scanf("%f", &height);

    printf("Your name is %sYour age is %d\nYour height is %.1f", firstName, age, height);
}
