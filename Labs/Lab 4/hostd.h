/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef HOSTD_H_
#define HOSTD_H_

// Include any relevant data structures here thay may be needed

// Include any relevant functions declarations here they must start with the
// extern keyword such as in the following example:
// extern void print_process(proc process);

// Reads the contents of a file and stores them in a string.
extern void read_file(FILE* file, char* buffer, size_t size);

// Init all queues
extern void init_all_queues();

// Load the dispatch list
extern void load_dispatchlist();

// Categorize Jobs into priority queues
extern void load_priority_queues();
#endif /* HOSTD_H_ */