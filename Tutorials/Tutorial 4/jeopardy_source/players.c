/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

#define BUFFER_LEN 256

// Initializes player names and stores in system
void initialize_players(struct player *players, int NUM_PLAYERS) {
    int i = 0;

    while(i < NUM_PLAYERS) {
        printf("What's your name player %d? \n", i);
        scanf("%s", players[i].name);
        players[i].score = 0;

        printf("Welcome %s! Score: %d\n", players[i].name, players[i].score);

        i++;
    }
}

// Returns true if the player name matches one of the existing players
bool player_exists(struct player *players, int num_players, char *name) {
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(struct player *players, int num_players, char *name, int score) {
    
}
