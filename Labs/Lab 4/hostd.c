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
queue Processes, RealTime, Jobs, P1, P2, P3;

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
  init_queue(&Processes);
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
        push(&Processes, process);
	}
}

void load_priority_queues(queue *q){
    if(q->head == NULL)
        return;
    
    node process = pop(q);

    while(process != NULL){
        switch(process->priority) {
        case 0:
            push(&RealTime, process);
            break;
        case 1:
            push(&P1, process);
            break;
        case 2:
            push(&P2, process);
            break;
        case 3:
            push(&P3, process);
            break;
        default:
            break;			
        }
        process = pop(q);
    }
}

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    
    // Load the dispatchlist
  	FILE *file = fopen("dispatchlist", "r");
  	init_all_queues();
  	
  	load_dispatchlist(file);
    
    load_priority_queues(&Processes);

    printf("Real Time\n");
    printf("--------------\n");
    print_queue(&RealTime);
    printf("--------------\n");
    printf("Priority 1\n");
    printf("--------------\n");
    print_queue(&P1);
    printf("--------------\n");
    printf("Priority 2\n");
    printf("--------------\n");
    print_queue(&P2);
    printf("--------------\n");
    printf("Priority 3\n");
    printf("--------------\n");
    print_queue(&P3);
    printf("--------------\n");
  	
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
