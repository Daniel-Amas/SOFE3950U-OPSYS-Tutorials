#include <stdlib.h>
#include <stdio.h>

struct Student{
    int studentId, age, startYear;
};

void save_student(struct Student student){
    FILE* stuFile = fopen("students.txt", "a");

    if (stuFile == NULL){
        perror("Error: File cannot be opened");
        return;
    }

    fprintf(stuFile, "%d, %d, %d\n", student.studentId, student.age, student.startYear);

    fclose(stuFile);
}

int main(){

    struct Student newStudent;

    printf("Enter your Student ID:\n");
    scanf("%d", &newStudent.studentId);

    printf("Enter your Age:\n");
    scanf("%d", &newStudent.age);

    printf("Enter the year you started at OTU:\n");
    scanf("%d", &newStudent.startYear);

    //save the new student with the void function
    save_student(newStudent);
    printf("Student information saved to students.txt\n");


    return 0;
}