// Program to calculate the sum of n numbers entered by the user

#include <stdio.h>
#include <stdio.h>
int main(){
    int n, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    ptr = (int*) malloc(n * sizeof(int));

    //if memory cannot be allocated
    if(ptr == NULL){
        printf("Error! memory not allocated.");
        exit(0);
    }

    printf("Enter elements: ");
    for(i = 0; i < n; ++i)

    return 0;
}

