#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    int index = 0;
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        for (int j = 200; j <= 800; j += 200)
        {
            snprintf(questions[index].category, MAX_LEN, "%s", categories[i]);
            snprintf(questions[index].question, MAX_LEN, "Sample Question %d", index + 1);
            snprintf(questions[index].answer, MAX_LEN, "Sample Answer %d", index + 1);
            questions[index].value = j;
            questions[index].answered = false;
            index++;
        }
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (!questions[i].answered)
        {
            printf("%s - $%d\n", questions[i].category, questions[i].value);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    // find the question with the given category and value and display it
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (!questions[i].answered && strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            printf("Category: %s\nValue: $%d\n%s\n", questions[i].category, questions[i].value, questions[i].question);
            break;
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (!questions[i].answered && strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            return (strcmp(questions[i].answer, answer) == 0);
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            return questions[i].answered;
        }
    }
    return false;
}
