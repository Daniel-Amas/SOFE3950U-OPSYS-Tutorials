#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    // Simple tokenization assuming space as a delimiter
    char *token = strtok(input, " ");
    *tokens = token;
    token = strtok(NULL, " ");
    if (token != NULL) {
        strcat(*tokens, " ");
        strcat(*tokens, token);
    }
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players)
{
    // Sort players by score
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = i + 1; j < num_players; j++) {
            if (players[i].score < players[j].score) {
                // Swap players
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    // Display results
    printf("Game Results:\n");
    for (int i = 0; i < num_players; ++i) {
        printf("%d. %s - Score: %d\n", i + 1, players[i].name, players[i].score);
    }
    exit(EXIT_SUCCESS);
}

int main(void)
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    int num_players = 0;
    
    // Input buffer and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players' names
    printf("Enter names of %d players:\n", NUM_PLAYERS);
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        printf("Player %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].score = 0;
        num_players++;
    }

    // Perform an infinite loop getting command input from users until the game ends
    int currentPlayerIndex = 0; // Initialize the current player index
    while (1)
    {
        // Call functions from the questions and players source files
        display_categories();
        printf("Enter category and dollar value (e.g., 'programming 200'): ");
        scanf("%s", buffer);

        // Tokenize the user input
        char *tokens[3];
        tokenize(buffer, tokens);
        char *category = tokens[0];
        int value = atoi(tokens[1]);

        // Find the question index based on category and value
        int questionIndex = -1;
        for (int i = 0; i < NUM_QUESTIONS; i++)
        {
            if (!questions[i].answered && strcmp(questions[i].category, category) == 0 && questions[i].value == value)
            {
                questionIndex = i;
                break;
            }
        }

        // Display the question
        display_question(category, value);
        printf("Enter your answer: ");
        scanf("%s", buffer);

        // Check if the answer is correct
        if (valid_answer(category, value, buffer))
        {
            // Update the score if the answer is correct
            update_score(players, num_players, players[currentPlayerIndex].name, value);
            printf("Correct! Player %s earns $%d.\n", players[currentPlayerIndex].name, value);
        }
        else
        {
            printf("Incorrect! The correct answer is: %s\n", questions[questionIndex].answer);
        }

        // Move to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % num_players;

        // Check if all questions have been answered
        if (all_questions_answered())
        {
            // Display the final results and exit
            show_results(players, num_players);
            break;
        }
    }
    return EXIT_SUCCESS;
}
