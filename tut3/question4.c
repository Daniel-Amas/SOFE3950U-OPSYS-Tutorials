#include <stdio.h>
#include <stdlib.h>

int main(){
#include <stdio.h>
    // create pointers
    int num_students;
    char *professor;
    int *student_ids, *grades;

    //allocate 256 characters to prof pointer using calloc
    professor = (char*)calloc(256, sizeof(char));

    if (professor == NULL){
        perror("Error: Could not allocate memory for professor");
        return 1;
    }

    //Prompt professor for name and number of students to mark
    printf("Professor Name:\n");
    fgets(professor, 256, stdin);
    printf("Enter number of students to mark: ");
    scanf("%d", &num_students);

    //allocate memory for student ids and grades
    student_ids = (int*)malloc(num_students * sizeof(int));
    grades = (int*)malloc(num_students * sizeof(int));

    // Check if malloc was successful
    if (student_ids == NULL || grades == NULL) {
        perror("Error allocating memory for student_ids or grades");
        return 1;
    }

    //free all allocated memory
    free(professor);
    free(student_ids);
    free(grades);

    return 0;
}