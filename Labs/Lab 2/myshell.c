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

const char *SHELL = "Project-Shell v0.1";
const char PROMPT[] = ">>";
char CWD[1024]; // will store the working directory

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
	
	// TODO: need to parse command line input from argv[]

	getcwd(CWD, sizeof(CWD)); // get working directory
	printf("%s %s", CWD, PROMPT);

	// Perform an infinite loop getting command input from users
	while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {

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

		if (strcmp(command, "help") == 0) {
			showHelp();
		}
		
		else if (strcmp(command, "pause") == 0) {
			char input[255];
			printf("%s\n", "Paused: Press Enter to resume");
			fgets(input,sizeof(input),stdin);
			while(input[0]!='\n'){}
		}
	
		else if (strcmp(command, "cd") == 0) {
			printf("you typed cd with arguments %s\n", arg);
			
			// if no <directory> specified, stay in cwd
			if (strlen(arg) == 0) {
				printf("no <directory> defined, remaining in current directory\n");
			} else {
				// change dir and display error if not found
				if (chdir(arg) != 0)
					perror("sh");
				else
					getcwd(CWD, sizeof(CWD));
			}
		}

		else if (strcmp(command, "clr") == 0) {
			int i;
			for(i=0;i<50;i++)
				printf("\n");
		}

		else if (strcmp(command, "dir") == 0) {
			DIR *dir;
			struct dirent *dp; 
			
			if (strlen(arg) == 0) {
				fprintf(stderr, "sh: expected argument to \"dir\"\n");
			} else {
				dir = opendir(arg); 
				
				while((dp = readdir(dir))!=NULL)
				{
					printf("%s\t",dp->d_name);
				}

				printf("\n%s", " ");

				closedir(dir);
			}
		}

		else if (strcmp(command, "echo") == 0) {
			if (strlen(arg) == 0) {
				fprintf(stderr, "sh: expected argument to \"cd\"\n");
			} else {
				printf("%s\n", arg);
			}
		}

		// display environment variables
		else if (strcmp(command, "environ") == 0) {
			printf(" SHELL: %s\n CWD: %s\n", SHELL, CWD);
		}

		// exit shell
		else if (strcmp(command, "quit") == 0) {
			printf("Exiting shell\n");
			return EXIT_SUCCESS;
		}

		// Unsupported command
		else {
			fputs("Unsupported command, use help to display the manual\n", stderr);
		}

		printf("%s %s", CWD, PROMPT); // print working directory + prompt
	}
	return EXIT_SUCCESS;
}
