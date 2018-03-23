/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef QUEUE_H_
#define QUEUE_H_

//#include "utility.h"
#include <stdbool.h>
#include "utility.h"

// Your linked list structure for your queue
// typedef ... 
//  ...
//  proc process;
//  ...
//} node_t; 

typedef struct queue {
  node head;
  node tail;
} queue;

// Include your relevant FIFO queue functions declarations here they must start 
// with the extern keyword such as in the following examples:

// Add a new process to the queue, returns the address of the next node added
// to the linked list

// extern node_t *push(node_t *tail, proc process);

// extern node_t *pop(node_t *tail);

extern void init_queue(queue *q);
extern bool isQueueEmpty(queue q);
extern void push(queue *q, node data);
extern node pop(queue *q);
extern void print_queue(queue *q);
#endif /* QUEUE_H_ */