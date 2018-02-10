/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

const char PROMPT[] = ">>";

// Define functions declared in myshell.h here

void showHelp() {
	FILE *f = fopen("README.md", "r");
	char row[255];
	while (fgets(row, sizeof(row), f) != NULL)
		puts(row);
	fclose(f);
}

int main(int argc, char *argv[]) {

    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
	char* token;

    // Parse the commands provided using argc and argv
	
	printf("%s", PROMPT);

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {

		// remove newline characters
		token = strtok(buffer, "\n");
		// get command
		token = strtok(buffer, " ");
		strcpy(command, token);

		// get arguments
		token = strtok(NULL, " "); // check if arguments exist
		if (token != NULL) {
			strcpy(arg, token);
			while (1) {
				token = strtok(NULL, " ");
				if (token == NULL)
					break;
				strcat(arg, " ");
				strcat(arg, token);
			}
		}

        // COMAND IMPLEMENTATION

		if (strcmp(command, "help") == 0) {
			showHelp();
		}
	
		else if (strcmp(command, "cd") == 0) {
			printf("you typed cd with arguments %s\n", arg);
        }

        // quit command -- exit the shell
		else if (strcmp(command, "exit") == 0) {
			printf("Exiting shell\n");
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

		// print prompt
		printf("%s", PROMPT);
    }
    return EXIT_SUCCESS;
}
