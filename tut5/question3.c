#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define Max_Threads 5

void* bellcurve (void student);

struct student{
    char name[50];
    int id;
    float grade;
};

void bellcurve (void students){
    struct studentstd = (struct student) students;
              printf(" Student Id is: %d \n", std->id);
                  printf(" Student Name is: %s \n", std->name);
             float j = std->grade 1.50;
            printf ("Student's Bellcurve grade : %f \n", j);

}

int main(){

    pthread_t thread[Max_Threads];
    struct student students[5];

    for(int i = 0; i < 5; i++){
        printf("\nStudent %d name: ", i + 1);
        scanf("%s", &students[i].name);

        printf("Student %d id: ", i + 1);
        scanf("%s", &students[i].id);

        printf("Student %d grade: ", i + 1);
        scanf("%f", &students[i].grade);
    } 

    for(int i = 0; i < 5; i++){
        int j = pthread_create(&thread[i], NULL, bellcurve, &students[i]); 
        if(j != 0){
        printf("Error:can not create thread, %d \n", j);
        exit(-1);
    }
    }

    for(int i = 0; i < 5; i++){
        pthread_join(thread[i], NULL);
    }

    return 0;
}