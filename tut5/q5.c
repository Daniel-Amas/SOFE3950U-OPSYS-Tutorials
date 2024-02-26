#define _XOPEN_SOURCE 600 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 
#include <errno.h> 
#define NUM_GRADES 10

//Global Variables
int grades[NUM_GRADES];
int total_grade = 0;
int total_bellcurve = 0;
pthread_barrier_t barrier;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *read_grades(void *arg){
    FILE *file = fopen("grades.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_GRADES; ++i) {
        fscanf(file, "%d", &grades[i]);
    }

    fclose(file);

    // Signal that grades have been read
    if (pthread_barrier_wait(&barrier) != 0 && errno != 0) {
        perror("Error waiting on barrier");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}

void *save_bellcurve(void *arg){
    int grade = *(int *)arg;
    int bellcurve = grade * 1.50;

    // Wait for all grades to be read
    if (pthread_barrier_wait(&barrier) != 0 && errno != 0) {
        perror("Error waiting on barrier");
        exit(EXIT_FAILURE);
    }

    // Update total_grade with mutual exclusion
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Error locking mutex");
        exit(EXIT_FAILURE);
    }

    total_grade += grade;

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Error unlocking mutex");
        exit(EXIT_FAILURE);
    }

    // Update total_bellcurve with mutual exclusion
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Error locking mutex");
        exit(EXIT_FAILURE);
    }

    total_bellcurve += bellcurve;

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Error unlocking mutex");
        exit(EXIT_FAILURE);
    }

    // Save bellcurve to file
    FILE *bellcurve_file = fopen("bellcurve.txt", "a");
    if (bellcurve_file == NULL) {
        perror("Error opening bellcurve file");
        exit(EXIT_FAILURE);
    }

    fprintf(bellcurve_file, "%d\n", bellcurve);

    fclose(bellcurve_file);

    pthread_exit(NULL);
}

int main(){
    pthread_t read_thread;
    pthread_t bellcurve_threads[NUM_GRADES];

    // Initialize barrier
    if (pthread_barrier_init(&barrier, NULL, NUM_GRADES + 1) != 0) {
        perror("Error initializing barrier");
        return EXIT_FAILURE;
    }

    // Create the thread to read grades
    if (pthread_create(&read_thread, NULL, read_grades, NULL) != 0) {
        perror("Error creating read thread");
        return EXIT_FAILURE;
    }

    // Create threads for bellcurve
    for (int i = 0; i < NUM_GRADES; ++i) {
        if (pthread_create(&bellcurve_threads[i], NULL, save_bellcurve, (void *)&grades[i]) != 0) {
            perror("Error creating bellcurve thread");
            return EXIT_FAILURE;
        }
    }

    // Wait for the reading thread to finish
    pthread_join(read_thread, NULL);

    // Wait for all bellcurve threads to finish
    for (int i = 0; i < NUM_GRADES; ++i) {
        pthread_join(bellcurve_threads[i], NULL);
    }

    // Destroy the barrier
    if (pthread_barrier_destroy(&barrier) != 0) {
        perror("Error destroying barrier");
        return EXIT_FAILURE;
    }

    // Print results
    printf("Total Grade before bellcurve: %d\n", total_grade);
    printf("Total Grade after bellcurve: %d\n", total_bellcurve);
    printf("Class Average before bellcurve: %.2f\n", (float)total_grade / NUM_GRADES);
    printf("Class Average after bellcurve: %.2f\n", (float)total_bellcurve / NUM_GRADES);

    return EXIT_SUCCESS;
}