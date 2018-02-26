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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

#define DELIM " "

// Put global environment variables here
int game_state;

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
char **tokenize(char *input){
    char *token;
    char **tokens = malloc(BUFFER_LEN * sizeof(char*));

    // Init token with command
    token = strtok(input, DELIM);
    int position = 0;

    // Retrieve all tokens
    while( token != NULL ) {
        // Trim extra space at the end
        if(token[strlen(token)] == ' '){
            token[strlen(token)] = 0;
        }

        // Remove \n characters
        if(strstr(token, "\n") != NULL){
            token = strtok(token, "\n");
        }

        tokens[position] = token;
        position++;
        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players, int num_players);

int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    struct player players[NUM_PLAYERS];

    strcpy(players[0].name, "a");
    strcpy(players[1].name, "s");
    strcpy(players[2].name, "d");
    strcpy(players[3].name, "f");
    
    // Buffer for user input
    char buffer[BUFFER_LEN] = { 0 };
    char chosen_option[BUFFER_LEN];
    char chosen_player[BUFFER_LEN];
    char answer[BUFFER_LEN];

    char **tokenized_chosen_option = malloc(BUFFER_LEN * sizeof(char*));
    char **tokenized_answer = malloc(BUFFER_LEN * sizeof(char*));

    int bytes_read;

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    //initialize_players(players, NUM_PLAYERS);
    
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    game_state = 1;
    while (game_state)
    {

        // Call functions from the questions and players source files
        display_categories();

        do {
            printf("%s\n", "Who's turn is it? Enter your name: ");
            fgets(chosen_player, BUFFER_LEN, stdin);
        } while(!player_exists(players, NUM_PLAYERS, chosen_player));
        
        do {
            printf("%s Choose your category and price!\n", chosen_player); 
            printf("(Make sure to use a '-' as your delimiter)\n");

            fgets(chosen_option, BUFFER_LEN, stdin);
            tokenized_chosen_option = tokenize(chosen_option);
        } while(already_answered(tokenized_chosen_option[0], atoi(tokenized_chosen_option[1])));
        
        display_question(tokenized_chosen_option[0], atoi(tokenized_chosen_option[1]));

        fgets(answer, BUFFER_LEN, stdin);
        tokenized_answer = tokenize(answer);

        if (valid_answer(tokenized_chosen_option[0], atoi(tokenized_chosen_option[1]), tokenized_answer[2])) {
            printf("Correct!");
        } else {
            printf("Incorrect!");
        }
        
        // Display the final results and exit
        if(!game_state){
            printf("Works!");
            game_state = 1;
        }
    }
    return EXIT_SUCCESS;
}
