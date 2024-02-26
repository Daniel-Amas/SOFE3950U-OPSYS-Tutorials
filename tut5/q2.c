#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *bellcurve(void *arg){
    int *grade = (int *)arg;

    //multiply grade by 1.50 (bell curve)
    double curvedGrade = (*grade) * 1.50;

    printf("Bell curved grade: %.2f\n", curvedGrade);

    pthread_exit(NULL);
}

//Global array of grades and threads
int grades[5];
pthread_t threads[5];

int main () {
    printf("Enter grades for 5 students: \n");

    for(int i =0; i<5; i++){
        printf("Student %d grade: ", i + 1);
        scanf("%d", &grades[i]);
    }

    //create 5 threads 
    for (int i=0; i<5; i++){
        if (pthread_create(&threads[i], NULL, bellcurve, &grades[i]) != 0){
            perror("Error creating thread");
            return EXIT_FAILURE;
        }
    }

    for(int i = 0; i<5;i++){
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}