#define _XOPEN_SOURCE 600 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 

void *class_total(void *arg){
    int grade = *(int *)arg;

    //Acquire the lock before updating the total grade
    pthread_mutex_lock(&mutex);

    total_grade += grade;

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

//Global Variables
int grades[10];
int total_grade = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    printf("Enter grades for ten students:\n");

    //Prompt for student grades
    for (int i = 0; i < 10; i++){
        printf("Student %d grade: ", i + 1);
        scanf("%d", &grades[i]);
    }

    //Create Threads
    pthread_t threads[10];
    for (int i = 0; i < 10; i++){
        if(pthread_create(&threads[i], NULL, class_total, ()&grades[i]) != 0){
            perror("Error creating Thread");
            return EXIT_FAILURE;
        }
    }

    //Wait for all threads to finish
    for (int i = 0; i<10; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Total Grade: %d\n");

    return EXIT_SUCCESS;
}