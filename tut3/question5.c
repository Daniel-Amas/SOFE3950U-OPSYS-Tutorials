#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Grade {
    int student_id;
    int mark;
};

void grade_students (struct Grade *grades, int num_students){
    //open or create grades.txt
    FILE * filePointer = fopen("grades.txt", "w");
    if(filePointer == NULL){//check if file was opened
        perror("Error: could not open file");
        
    }

    int sum = 0;
    double avg, std_deviation = 0.0;

    //iterate through Grade struct
    for(int i = 0; i < num_students; i++){
        //write student id and mark to the file
        sum += grades[i].mark;

        fprintf(filePointer, "%d %d\n", grades[i].student_id, grades[i].mark);
    }

    //calculate average
    avg = (double)sum/num_students;

    //calculate std_deviation
    for (int i = 0; i< num_students; i++){
        std_deviation += pow(grades[i].mark - avg, 2);
    }
    std_deviation /= num_students;
    std_deviation = sqrt(std_deviation);

    // Write average and standard deviation to the file
    fprintf(filePointer, "Average: %lf\nStandard Deviation: %lf\n", avg, std_deviation);

    // Close the file
    fclose(filePointer);

}

int main(){
    //create char pointer for professor's name and struct pointer for the grade struct
    char *professor = (char *)calloc(256, sizeof(char));
    struct Grade *grades;

    //Prompt professor for name and number of students to mark
    printf("Enter Professor Name:\n");
    fgets(professor, 256, stdin);
    int num_students;
    printf("Enter number of students to mark: ");
    scanf("%d", &num_students);

    //Allocate memory for the grades
    grades = (struct Grade *)malloc(num_students * sizeof(struct Grade));

    // Check if memory allocation was successful
    if (grades == NULL) {
        printf("Memory allocation failed.\n");
        free(professor);
        return 1; // Exit with an error code
    }

    // Prompt professor for student id and mark for each student
    for (int i = 0; i < num_students; i++) {
        printf("Enter student %d id: ", i + 1);
        scanf("%d", &grades[i].student_id);

        printf("Enter student %d mark: ", i + 1);
        scanf("%d", &grades[i].mark);
    }

    // Call the function to grade students and calculate statistics
    grade_students(grades, num_students);

    // Free allocated memory before terminating
    free(professor);
    free(grades);

    return 0;
}