#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void) {
    // Initialization of questions array
    srand(time(NULL));

    for (int i = 0; i < NUM_CATEGORIES; ++i) {
        for (int j = 0; j < NUM_QUESTIONS / NUM_CATEGORIES; ++j) {
            strcpy(questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].category, categories[i]);
            sprintf(questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].question, "Question %d", j + 1);
            sprintf(questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].answer, "Answer %d", j + 1);
            questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].value = (j + 1) * 100;
            questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].answered = false;
        }
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
    // Displaying categories and dollar values
    for (int i = 0; i < NUM_CATEGORIES; ++i) {
        printf("%s\n", categories[i]);
        for (int j = 0; j < NUM_QUESTIONS / NUM_CATEGORIES; ++j) {
            if (!questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].answered) {
                printf("$%d  ", questions[i * (NUM_QUESTIONS / NUM_CATEGORIES) + j].value);
            } else {
                printf("     ");
            }
        }
        printf("\n");
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value) {
    // Displaying a question
    for (int i = 0; i < NUM_QUESTIONS; ++i) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            printf("Category: %s\n", questions[i].category);
            printf("Value: $%d\n", questions[i].value);
            printf("Question: %s\n", questions[i].question);
            break;
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer) {
    // Validating the answer
    for (int i = 0; i < NUM_QUESTIONS; ++i) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return (strcmp(questions[i].answer, answer) == 0);
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value) {
    // Checking if the question has already been answered
    for (int i = 0; i < NUM_QUESTIONS; ++i) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}