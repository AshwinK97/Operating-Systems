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

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for(int i = 0; i < NUM_QUESTIONS; i++){
        strcpy(questions[i].category, categories[i%3]);
        printf("%s\n", questions[i].category);

        strcpy(questions[i].question, categories[i%3]); 
        printf("%s\n", questions[i].question);

        strcpy(questions[i].answer, "Answer");
        printf("%s\n", questions[i].answer);
        
        questions[i].value = ((i/3) * 100) + 100;
        printf("%d\n", questions[i].value);
        
        questions[i].answered = false;
        printf("%s", questions[i].answered ? "true\n" : "false\n");
        printf("--------------\n");
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for(int i = 0; i < NUM_QUESTIONS; i++){
        printf("%s\n", questions[i].category);
        printf("%d\n", questions[i].value);
        printf("--------------\n");
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
