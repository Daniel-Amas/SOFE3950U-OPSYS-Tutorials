#include <stdio.h>

int main ()
{
    int newArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < sizeof(newArr)/sizeof(newArr[0]); i++){
        printf("%d\n", newArr[i]);
    }

    return 0;
}