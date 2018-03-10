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
#define SCREENBUFFER 100

// Put global environment variables here
int PID;
char SHELL[BUFFER_LEN];
const char *PROMPT = ">>";
char PWD[BUFFER_LEN];

// Define functions declared in myshell.h here

void showHelp() {
	FILE *f = fopen("README.md", "r");
	char row[255];
	while (fgets(row, sizeof(row), f) != NULL)
		printf("%s", row);
	fclose(f);
}

int main(int argc, char *argv[]) {

	// File pointer for batch file
	FILE *bfp;

	// Input buffer and and commands
	char buffer[BUFFER_LEN] = { 0 };
	char command[BUFFER_LEN] = { 0 };
	char arg[BUFFER_LEN] = { 0 };
	char* token;

	// TODO: need to parse command line input from argv[]

	// set PWD
	getcwd(PWD, sizeof(PWD));

	// get PID
	PID = getpid();

	// set SHELL to path in /prov/2636/exe
	char linkpath[50];
	sprintf(linkpath, "/proc/%d/exe", PID);
	readlink(linkpath, SHELL, BUFFER_LEN);

	// if batchfile was provided, setup file pointer
	if (argc > 1) {
		if ((bfp = fopen(argv[1], "r")) == 0) {
			perror(argv[1]);
			return EXIT_SUCCESS;
		}
	}

	// Perform an infinite loop getting command input from users
	while (1) {

		// reset command buffers
		buffer[0] = '\0';
		command[0] = '\0';
		arg[0] = '\0';

		// print prompt
		printf("%s%s ", PWD, PROMPT);

		// if batchfile was provided, read it
		if (argc > 1) {
			// if read is unnsuccessful, exit
			if (fgets(buffer, BUFFER_LEN, bfp) == NULL)
				strcpy(buffer, "exit");

			// if read is successful
			else {
				// check for empty line
				if (strlen(buffer) <= 1)
					continue;

				// display command and run it
				printf("Running: %s\n", buffer);
			}
		}

		// else get input from user, exit if input is null
		else if (fgets(buffer, BUFFER_LEN, stdin) == NULL) {
			printf("Exiting shell\n");
			return EXIT_SUCCESS;
		}

		// remove newline characters
		token = strtok(buffer, "\n");
		// get command
		token = strtok(buffer, " ");
		strcpy(command, token);

		// get arguments by tokenization
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

		// display help
		if (strcmp(command, "help") == 0) {
			showHelp();
		}

		// pause the shell
		else if (strcmp(command, "pause") == 0) {
			char input[255];
			printf("%s\n", "Paused: Press Enter to resume");
			do {
				fgets(input, sizeof(input), stdin);
			} while(input[0] != '\n');
		}

		// change directory
		else if (strcmp(command, "cd") == 0) {

			// if no <directory> specified, arg = PWD
			if (strlen(arg) == 0)
				strcpy(arg, PWD);

			// change dir, display error if not found
			if (chdir(arg) != 0)
				perror("sh");

			// if found, set new PWD
			else
				getcwd(PWD, sizeof(PWD));
		}

		// clear the screen
		else if (strcmp(command, "clr") == 0 || strcmp(command, "clear") == 0) {
			int i;
			for(i=0; i<SCREENBUFFER; i++) printf("\n");
		}

		// display contents of directory
		else if (strcmp(command, "dir") == 0 || (strcmp(command, "ls")) == 0) {
			DIR *dir;
			struct dirent *dp;

			// if no path specified, take PWD as <arg>
			if (strlen(arg) == 0)
				strcpy(arg, PWD);

			// open directory at path <arg>
			dir = opendir(arg);

			// if dir was not opened successfully
			if (dir == NULL)
				perror(arg);

			else {
				// read each item and write to screen
				while((dp = readdir(dir)) != NULL)
					printf("%s\t", dp->d_name);
				printf("\n");
			}

			// close directory
			closedir(dir);
		}

		// echo back comment
		else if (strcmp(command, "echo") == 0) {
			// if no <comment> is specified, set arg to empty string
			if (strlen(arg) == 0)
				strcpy(arg, "");
			printf("%s\n", arg);
		}

		// display environment variables
		else if (strcmp(command, "environ") == 0 || (strcmp(command, "env")) == 0) {
			printf(" PID: %d\n SHELL: %s\n PWD: %s\n", PID, SHELL, PWD);
		}

		// exit shell
		else if (strcmp(command, "quit") == 0 || (strcmp(command, "exit")) == 0) {
			printf("Exiting shell\n");
			return EXIT_SUCCESS;
		}

		// Unsupported command
		else {
			fputs("Unsupported command, use help to display the manual\n", stderr);
		}
	}

	// if batchfile was provided, close it before exiting
	if (argc > 1)
		fclose(bfp);

	return EXIT_SUCCESS;
}
