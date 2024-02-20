#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

#define BUFFER_LEN 256
#define NUM_PLAYERS 4




void tokenize(char *input, char **tokens);

int winner()

void show_results(player *players, int num_players);

int main(int argc, char *argv[])
    // Array of 4 players
    player players[NUM_PLAYERS+1];
    int test = 0;
    int rem_questions = NUM_OF_QUESTION-1; 

    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char *tokens[BUFFER_LEN] = { 0 };
    
    // Display the game introduction and questions
    initialize_game();
    printf("Welcome to Jeopardy!\n");
    printf("Please enter the names of the four players\n");

    for(int i=1; i<=NUM_PLAYERS; i++)
    {
    
        printf("Player %d?\t", i);
        fgets(players[i].name, BUFFER_LEN, stdin);
        if (players[i].name[strlen(players[i].name)-1] == '\n') 
        { 
            players[i].name[strlen(players[i].name)-1] = '\0'; 
            }     
	  players[i].score = 0; // initialise score to 0
    
    }
    
    system("clear"); //clear screen

    char cat[BUFFER_LEN] = { 0 }; //question category
    int value = 0;
    char *token;
    int player = 1;
    int j = -1;

    while (1) 
    {
        j = -1;
        test = 0;
        value = 0;
        printf("%s? \n", players[player].name);
        display_categories();
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strlen(buffer)-1] = '\0';

    for (int i=0; i<strlen(buffer); i++)
    {
        if (buffer[i] == ' ')
        {
            test++;
        } 
    }

    if (test == 1)
    {
        token = strtok(buffer, " ");
        strcpy(cat, token);
        token = strtok(NULL, " ");
        if (atoi(token))    value = atoi(token);
     
    }
        for(int jj = 0; jj < NUM_CATEGORIES; jj++) 
        {

            if ( (strcmp(cat, categories[jj]) == 0) && (value == 100 || value == 200 || 
		    value == 300 || value == 400 ) ){ 
                if ( already_answered(&categories[jj], value) ) 
                { continue;}
            
                printf("I hope you have knowledge on %s. We've got %d on the line.\n", categories[jj], value); 
                j = jj;

            
            }
           
        } 
        if (j == -1)
        {
            printf("Can you come again? I didn't get that.\n");
            continue;
        } 
        
	
        display_question(&categories[j], value);
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strlen(buffer)-1] = '\0';

        if (valid_answer(&categories[j], value, buffer))
        {
                    if (value == 100)
                        printf("Aamzing.\n");
                    else if (value == 200)
                            printf("Good Job.\n");
                    else if (value == 300)
                            printf("Exceptional.\n");
                    else if (value == 400)
                            printf("Good Job.\n");
                    
                    
                    update_score(players, player, value); 
        }

        else
        {
                    if (value == 100)
                        printf("Incorrect?\n");
                    else if (value == 200)
                            printf("Wrong.\n");
                    else if (value == 300)
                            printf("Try again. Not.\n");
                    else if (value == 400)
                            printf("wrong again .\n");
                    
        }
                
                
        if (rem_questions)
        {
                    rem_questions--;
                  
            if (player == NUM_PLAYERS)
                    {
                        printf("show them the leaderboard: \n");
                        show_results(players);
                        printf("New Round.");
                        fgets(buffer, BUFFER_LEN, stdin); 
                       player = 1;
                    }

            else
                    {	
                        printf("we have %s with %d points\n", players[player].name, players[player].score);
                        printf(" next player");
                       player += 1;
                        fgets(buffer, BUFFER_LEN, stdin); 
                    }
                
            system("clear");
                    
                    }
            
        else 
                {
                printf("Game over, the winner is %s with %d points. Congratulations.\n", 
			players[winner(players)].name,players[winner(players)].score);
                return EXIT_SUCCESS;
                }
                
            }
            

    return EXIT_SUCCESS; 
}



int winner(player1 *players)
{
    int max = 0;
	int best = 0;
	int tie = 0;
	
    for (int i = 1; i <=NUM_PLAYERS; i++)
	{
	    if (players[i].score > max)
	    {
            max = players[i].score; 
            best = i; 
            }
	    if (players[i].score == max){
		tie = i;
		}

	}
	
	return best; 
}

void show_results(player1 *players)
{
   
    for (int i =1; i<=NUM_PLAYERS; i++)
    {
        printf("%s: %-5d", players[i].name, players[i].score);
    }
    printf("\n");
 
}

void tokenize(char *input, char **token)
{
  	if (input[strlen(input)-1] == '\n') { input[strlen(input)-1] = '\0'; }     
	char *p = strtok(input, token);
	while(p != NULL) {
	    printf("%s\n", p);
	    p = strtok(NULL, token);
	}
}
