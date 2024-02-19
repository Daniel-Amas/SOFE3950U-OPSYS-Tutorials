/*
 * Tutorial 4 / player.c
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    for (int i = 0; i<num_players;i++)
    {
        if(strcmp(players[i].name,name)==0)
        {
            return true;
        }
    }
    return false;
}

// Go through the list of players and update the score for the player with the corresponding name
void update_score(player *players, int num_players, char *name, int score)
{
    for (int i = 0; i<num_players;i++)
    {
        if(strcmp(players[i].name,name)==0)
        {
            players[i].score = players[i].score + score;
        }
    }
}
