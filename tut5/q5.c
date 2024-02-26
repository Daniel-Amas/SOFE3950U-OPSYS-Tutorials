#define _XOPEN_SOURCE 600 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 

void *read_grades(void *arg){
    FILE *file = fopen("grades.txt", "r");
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++){
        fscanf(file, "%d", &grades[i]);
    }

    fclose(file);

    //signal the barrier
    pthread_barrier_wait(&barrier);

    pthread_exit(NULL);
}

void *save_bellcurve(void *arg){
    int grade = *(int *)arg;

    //Wait for all grades to be read
    pthread_barrier_wait(&barrier);

    //Apply bell curve 
    double bellcurve = grade * 1.50;

    pthread_mutex_lock(&mutex);
    total_grade += grade;
    total_bellcurve += bellcurve;
    pthread_mutex_unlock(&mutex);

    FILE *file = fopen("bellcurve.txt", "a");
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%.2f\n", bellcurve);

    fclose(file);

    pthread_exit(NULL);
}

//Global Variables
int grades[10];
int total_grade = 0;
double total_bellcurve = 0.0;
pthread_barrier_t barrier;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    pthread_barrier_init(&barrier, NULL, 11);

    //create thread to read grades
    pthread_t readThread;
    if(pthread_create(&readThread, NULL, read_grades, NULL) != 0){
        perror("Error creating read thread");
        return EXIT_FAILURE;
    }

    //threads to save grades
    pthread_t saveThreads[10];
    for (int i = 0; i < 10; i++){
        if(pthread_create(&readThread, NULL, read_grades, NULL) != 0){
            perror("Error creating save thread");
            return EXIT_FAILURE;
        }
    }

    pthread_join(readThread, NULL);

    for (int i = 0; i<10; i++){
        pthread_join(saveThreads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    printf("Total Grade Before Bellcurve: %d\n", total_grade);
    printf("Class Average Before Bellcurve: %.2f\n", (double)total_grade / 10);
    printf("Total Bellcurved Grade: %.2f\n", total_bellcurve);
    printf("Class Average After Bellcurve: %.2f\n", total_bellcurve/10);

    return EXIT_SUCCESS;
}