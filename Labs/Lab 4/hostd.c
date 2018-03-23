/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"


// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
queue q, RealTime, Jobs, P1, P2, P3;

// Define functions declared in hostd.h here

// Reads the contents of a file and stores them in a string.
void read_file(FILE* file, char* buffer, size_t size) {
	int i;
	for(i = 0; !feof(file) && i < size; i++)
		buffer[i] = fgetc(file);

	buffer[i - 1] = '\0';	//Add the terminating null character.
}

// Init all queues to be filled
void init_all_queues(){
  init_queue(&RealTime);
  init_queue(&Jobs);
  init_queue(&P1);
  init_queue(&P2);
  init_queue(&P3);
}

// Read processes from list and load into appropriate queue
void load_dispatchlist(FILE *file){
  unsigned int SIZE = 2048;
  char* buffer = malloc(SIZE);
  while(!feof(file)){
	  fgets(buffer, SIZE, file);
	  char *token;
	  node process = malloc(sizeof(node_t));;
	  resources resource_list = malloc(sizeof(resources_t));;
	  
	  token = strtok(buffer, ",");
		sscanf(token, "%d", &process->arrival_time);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &process->priority);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &process->processor_time);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &process->size);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &resource_list->printers);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &resource_list->scanners);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &resource_list->modems);
		
		token = strtok(NULL, ",");
		sscanf(token, "%d", &resource_list->CD_drives);
		
		process->resource_list = resource_list;
	  
	  strtok(NULL, "\n");
	  
	  if(process->priority == 0){
	    push(&RealTime, process);
	  } else {
	    push(&Jobs, process);
	  }
	}
}

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    
    // Load the dispatchlist
  	FILE *file = fopen("dispatchlist", "r");
  	init_all_queues();
  	
  	load_dispatchlist(file);
    
    print_queue(&RealTime);
	print_queue(&Jobs);
  	
  	return 0;
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}
