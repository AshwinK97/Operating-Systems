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
#define CRITICAL_MEMORY 64

// Put global environment variables here
queue Processes, RealTime, Jobs, P1, P2, P3;
int dispatch_time = 0;
int timer = 0;
int status;
pid_t current_process;

// Define functions declared in hostd.h hereå

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

void start_process(node process){
    int pid = fork();	
    if(pid < 0)
        printf("Error: Process not created\n");
    else if (pid == 0) {
        execvp("./process", NULL);
    }
    else {
        process->pid = pid;
        process->status = 1;
    }
}

void resume_process(node process){
    if(kill(process->pid, SIGCONT) != 0) {
		printf("%d: SIGCONT failed.\n", process->pid);
		return;
	} 

    process->status = 1; 
}

void stop_process(node process){
    if(kill(process->pid, SIGTSTP) != 0) {
		printf("%d: SIGTSTP failed.\n", process->pid);
		return;
	} 
    
	waitpid(process->pid, &status, WUNTRACED); //Wait for process to be stopped before continuing execution
	if(process->priority < 3){
        free_mem(process->memory);
	    free_resources(process->resource_list);
    }
    process->status = 2; 
}

void kill_process(node process){
    // Send Sig to terminate
    if(kill(process->pid, SIGINT) != 0) {
		printf("Terminate of %d failed.\n", process->pid);
		return;
	}
	
    // Wait for process to be Terminated
	waitpid(process->pid, &status, WUNTRACED);

	// Free Memory and Resources
	if(process->priority != 0) {
		free_mem(process->memory);
		free_resources(process->resource_list);
	}
	process->status = 3;
}

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    // Load the dispatchlist
  	FILE *file = fopen("dispatchlist", "r");
  	init_all_queues();
  	
    // Add each process structure instance to the job dispatch list queue
  	load_dispatchlist(file);
  	
    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues
    load_priority_queues(&Processes);
    
    // Allocate the resources for each process before it's executed
    init_resources();
    alloc_mem(64);

    while(!isQueueEmpty(RealTime)){
        // Grab process from Queue
        node process = pop(&RealTime);
        bool enoughResources = false;
        bool enoughMemory = false;

        // Allocate process resources
        enoughResources = alloc_resources(process->resource_list);
        //process->memory = alloc_mem(process->size);

        if(process->memory != NULL)
            enoughMemory = true;
        
        if(!enoughResources){
            push(&RealTime, process);
            continue;
        }

        // Execute the process binary using fork and exec

        start_process(process);

        timer = 0;
        while(timer != process->processor_time){
            timer += 1;
            sleep(1);
        }

        // Perform the appropriate signal handling / resource allocation and de-alloaction
        kill_process(process);
        
        // Repeat until all processes have been executed, all queues are empty
    }

    while(!isQueueEmpty(P1)){
        // Grab process from Queue
        node process = pop(&P1);
        bool enoughResources = false;
        bool enoughMemory = false;

        // Allocate process resources
        enoughResources = alloc_resources(process->resource_list);
        process->memory = alloc_mem(process->size);

        if(process->memory != NULL)
            enoughMemory = true;
        
        if(!enoughResources || !enoughMemory){
            push(&P1, process);
            continue;
        }

        // Execute the process binary using fork and exec
        start_process(process);

        // Perform the appropriate signal handling / resource allocation and de-alloaction
        sleep(1);
        stop_process(process);

        process->processor_time -= 1;

        if(process->processor_time == 0){
            kill_process(process);
        } else {
            push(&P2, process);
        }
        // Repeat until all processes have been executed, all queues are empty
    }

    while(!isQueueEmpty(P2)){
        // Grab process from Queue
        node process = pop(&P2);
        bool enoughResources = false;
        bool enoughMemory = false;

        // Allocate process resources
        enoughResources = alloc_resources(process->resource_list);
        process->memory = alloc_mem(process->size);

        if(process->memory != NULL)
            enoughMemory = true;
        
        if(!enoughResources || !enoughMemory){
            push(&P2, process);
            continue;
        }

        // Execute the process binary using fork and exec
        if(process->status != 2){
            start_process(process);
        } else {
            resume_process(process);
        }

        // Perform the appropriate signal handling / resource allocation and de-alloaction
        sleep(1);
        stop_process(process);

        process->processor_time -= 1;

        if(process->processor_time == 0){
            kill_process(process);
        } else {
            push(&P3, process);
        }
        // Repeat until all processes have been executed, all queues are empty
    }

    while(!isQueueEmpty(P3)){
        // Grab process from Queue
        node process = pop(&P3);
        bool enoughResources = false;
        bool enoughMemory = false;

        // Allocate process resources
        enoughResources = alloc_resources(process->resource_list);
        process->memory = alloc_mem(process->size);

        if(process->memory != NULL)
            enoughMemory = true;
        
        if(!enoughResources || !enoughMemory){
            push(&P3, process);
            continue;
        }

        // Execute the process binary using fork and exec
        if(process->status != 2){
            start_process(process);
        } else {
            resume_process(process);
        }

        // Perform the appropriate signal handling / resource allocation and de-alloaction
        sleep(1);
        stop_process(process);

        process->processor_time -= 1;

        if(process->processor_time == 0){
            kill_process(process);
        } else {
            push(&P3, process);
        }
        // Repeat until all processes have been executed, all queues are empty
    }

    return EXIT_SUCCESS;
}
