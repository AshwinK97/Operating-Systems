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
    char buffer[BUFFER_LEN];

    while(i < NUM_PLAYERS) {
        printf("What's your name player %d? \n", i);
        fgets(buffer, BUFFER_LEN, stdin);

        // Remove \n characters
        size_t ln = strlen(buffer)-1;
        if (buffer[ln] == '\n')
            buffer[ln] = '\0';
        
        strcpy(players[i].name, buffer);
        players[i].score = 0;

        printf("Welcome %s! Score: %d\n", players[i].name, players[i].score);

        i++;
    }
}

// Returns true if the player name matches one of the existing players
bool player_exists(struct player *players, int NUM_PLAYERS, char *name) {
    int i = 0;
    
    // Remove \n characters
    if(strstr(name, "\n") != NULL){
        name = strtok(name, "\n");
    }

    // Check if player is in array
    while(i < NUM_PLAYERS) {
        if(strcmp(&players[i], name) == 0){
            return true;
        }
        i++;
    }
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(struct player *players, int NUM_PLAYERS, char *name, int score) {
    int i = 0;

    while(i < NUM_PLAYERS) {
        if(strcmp(&players[i], name) == 0){
            players[i].score += score;
            printf("%d\n", players[i].score);
        }
        i++;
    }
}

void display_results(struct player *players, int NUM_PLAYERS){

    // Sort the results
    for (int i = 0; i < NUM_PLAYERS; i++)
	{
		for (int j = 0; j < NUM_PLAYERS; j++)
		{
			if (players[j].score < players[i].score)
			{
				struct player tmp = players[i];
				players[i] = players[j];
				players[j] = tmp;
			}  
		}
	}

    // Print all results
    int k = 0;
    while(k < NUM_PLAYERS){
        printf("%d: %s %d\n", k+1, players[k].name, players[k].score);
        k++;
    }
}
