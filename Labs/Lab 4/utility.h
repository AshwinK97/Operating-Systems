/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_

// Include libraries
#include <stdbool.h>

// The amount of available memory
#define MEMORY 1024

// Resources structure containing integers for each resource constraint and an
// array of 1024 for the memory
// typedef struct {
//  ...
//  ...
// } resources;

// Processes structure containing all of the process details parsed from the 
// input file, should also include the memory address (an index) which indicates
// where in the resources memory array its memory was allocated
// typedef struct {
//  ...
//  ...
// } process;

// Using First Fit Algorithm

typedef struct memory_block_t {
  int offset;
  int size;
  bool allocated;
  struct memory_block_t *next;
  struct memory_block_t *previous;
} memory_block_t;
typedef memory_block_t *memory_block;

typedef struct resources_t {
  int printers;
  int scanners;
  int modems;
  int CD_drives;
} resources_t;
typedef resources_t *resources;

typedef struct node_t {
  int pid;
  int arrival_time;
  int priority;
  int processor_time;
  int size;
  int status;
  memory_block memory;
  resources resource_list;
  struct node_t *next;
} node_t;
typedef node_t *node;

// init Methods
extern void init_resources();

// Print methods for testing
extern void print_resource_list(resources resource_list);
extern void print_process(node process);
extern void print_memory_block(memory_block block);
extern void print_memory();

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following examples:

// Function to allocate a contiguous chunk of memory in your resources structure
// memory array, always make sure you leave the last 64 values (64 MB) free, should
// return the index where the memory was allocated at
// extern int alloc_mem(resources res, int size);
extern memory_block alloc_mem(int size);
extern memory_block split_block(memory_block block, int size);

// Resources Allocation and Release
extern bool resourcesAvailable(resources resource_list);
extern bool alloc_resources(resources resource_list);
extern void free_resources(resources resource_list);

// Function to free the allocated contiguous chunk of memory in your resources
// structure memory array, should take the resource struct, start index, and 
// size (amount of memory allocated) as arguments
// extern free_mem(resources res, int index, int size);
extern void free_mem(memory_block block);
extern void merge_blocks(memory_block front, memory_block back);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
// extern void load_dispatch(char *dispatch_file, node_t *queue);


#endif /* UTILITY_H_ */