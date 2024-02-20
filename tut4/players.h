
#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <stdbool.h>

#define MAX_LEN 256

// Player struct for each player
typedef struct {
    char name[MAX_LEN];
    int score;
} player;


extern bool player_exists(player *players, int num_players, char *name);

extern void update_score(player *players, int num_players, char *name, int score);

#endif
