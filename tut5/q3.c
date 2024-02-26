#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct Student {
    char name[50];
    int student_id;
    int grade;
};

void *bellcurve(void *arg){
    struct Student *student = (struct Student *)arg;

    //multiply grade by 1.50 (bell curve)
    double curvedGrade = student->grade * 1.50;

    printf("Student: %s\t, ID: %d\t, Bell curved grade: %.2f\n", student->name, student->student_id, curvedGrade);

    pthread_exit(NULL);
}

//Global variables
struct Student students[5];
pthread_t threads[5];

int main () {
    printf("Enter Student's name, ID, and grade: \n");

    for(int i =0; i<5; i++){
        printf("Student %d name: ", i + 1);
        scanf("%s", students[i].name);
        printf("Student %d ID: ", i + 1);
        scanf("%d", &students[i].student_id);
        printf("Student %d grade: ", i + 1);
        scanf("%d", &students[i].grade);
    }

    //create 5 threads 
    for (int i=0; i<5; i++){
        if (pthread_create(&threads[i], NULL, bellcurve, (void *)&students[i]) != 0){
            perror("Error creating thread");
            return EXIT_FAILURE;
        }
    }

    for(int i = 0; i<5;i++){
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}