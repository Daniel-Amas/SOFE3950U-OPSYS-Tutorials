#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

question quest[NUM_QUESTIONS] = {

{
    "Science",
    "What is the smallest unit of matter?",
    "ATOM",
    100,
    false
},

{
    "History",
    "Who is the first president of the United States?",
    "WASHINGTON",
    200,
    false
},

{
    "Drinks",
    "What is the main ingredient in a margarita",
    "TEQUILA", 
    300,
    false
},

{
    "Sports",
    "What is the most popular sport in the world?",
    "SOCCER",
    400,
    false
},

{
    "Technology",
    "What is the most popular programming language?",
    "JAVA",
    100,
    false
},
{
    "Animals",
    "What animal is known for its long neck",
    "GIRAFFE",
    200,
    false
},

{
    "Music",
    "What is the most popular music genre?",
    "POP",
     300,
    false
},

{
    "Food",
    "What is the most stolen grocery item?",
    "CHEESE",
    400,
    false
},

{
    "Lifestyle",
    "What is the most popular social media platform?",
    "FACEBOOK",
    100,
    false
},

{
    "Geography",
    "What is the capital of Canada?",
    "OTTAWA",
    200,
    false
},

{
    "Math",
     "What is the value of pi?",
    "3.14159...",
    300,
    false
},

{
    "Games",
    "What is the most popular video game?",
    "404",
    400,
    false
}
};

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize the questions struct and assign it to the questions array
     printf("Welcome to jeopardy.\n"
	 "Quick rundown of the rules: \n"
	 "1. To select a question, type the category and the value .\n"
	 "2. Answer in all caps, in 'WHO IS' or 'WHAT IS'. We don't care which.\n"
	 ;
  
}

// Displays each of the remaining questions and categories that have not been answered
void display_categories(void)
{
    // print categories and dollar values
    printf("We have\n");
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
            printf ("%-5s %-5s\t", categories[i], " ");
 
                for (int j = 0; j < 4; j++)
                {
                    if (quest[i*4 + j].answered == false)
                    {
                        printf("%-2d \t", quest[i*4 +j].value);
                    }
			        else printf("%-2s\t", " ");
                }
        
        printf("\n"); 
    }
    
    printf("Pick your question: ");
    
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
   //printf("%s  %d\n", category, value);
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        if ( ( strcmp(quest[i].category, category) == 0 ) && (quest[i].value == value) )
        {
        printf("\033[1;34m\t\t%s\033[0m\n", quest[i].question);
        quest[i].answered = true;
        break;
        }
    }
}


bool valid_answer(char *category, int value, char *answer)
{
    int test = 0;
    if (answer[strlen(answer)-1] == '\n') { answer[strlen(answer)-1] = '\0'; } //remove newline     
    for (int i=0; i<strlen(answer); i++)
    {
        if (answer[i] == ' ')
        {
            test++;
        }
    }

    if (! (test == 2) ) return false;
  	char *p = strtok(answer, " ");
    if ( !(strcmp(&p, "WHO") || strcmp(&p, "WHAT") ) ) return false; 
    if (p != NULL)  p = strtok(NULL, " ");
    if ( !strcmp(&p, "IS") ) return false;
    if (p != NULL)  p = strtok(NULL, " ");
    strcpy(answer, p);


    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        if ( ( strcmp(quest[i].category, category) == 0 ) && (quest[i].value == value) )
        {
            if ( strcmp(quest[i].answer, answer) == 0 ) 
            {
                return true;
            }
            else { return false; }
        }
    }
}


bool already_answered(char *category, int value)
{
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        if ( ( strcmp(quest[i].category, category) == 0 ) && (quest[i].value == value) )
        {
            if ( quest[i].answered == false ) 
            {
                return false;
            }
            else { return true; }
        }
    }

}
