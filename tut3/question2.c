#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    //file pointer variable. stores the value returned by fopen
    FILE* q2ptr;
    q2ptr = fopen("question2.txt", "r");
    int q2Numbers[10];

    //check if the file opens successfully
    if (q2ptr == NULL){
        printf("The file is not opened. The program will now exit.");
        exit(0);
    }

    //read input from the question2.txt into an q2Numbers array
    for(int i=0; i < sizeof(q2Numbers)/sizeof(q2Numbers[0]); i++){
        fscanf(q2ptr, "%d", &q2Numbers[i]);
    }

    //close file
    fclose(q2ptr);
    printf("question2.txt contains:\n");
    for(int i = 0; i < sizeof(q2Numbers)/sizeof(q2Numbers[0]); i++){
        printf("%d\n", q2Numbers[i]);
    }
    

    return 0;
}