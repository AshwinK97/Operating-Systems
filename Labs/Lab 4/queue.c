/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

// node_t *push(node_t *tail, proc process);
// {
//      ...
// }

// node_t *pop(node_t *tail);
// {
//      ...
// }


void print_queue(queue *q){
  if(q->head == NULL)
    return;
  
  node process = q->head;
  
  while(process->next != NULL){
    print_process(process);
    process = process->next;
  }
  
  print_process(process);
  return;
}

void init_queue(queue *q){
  q->head = NULL;
  q->tail = NULL;
}

bool isQueueEmpty(queue q){
  return q.head == NULL;
}

void push(queue *q, node data){
  data->next = NULL;

  if(!isQueueEmpty(*q))
		q->tail->next = data;
	else
		q->head = data;

	q->tail = data;
}

node pop(queue *q){
  if(q == NULL)
    return NULL;
  
  node head = q->head;

  if(head != NULL){
    q->head = head->next;
  }
  
  return head;
}