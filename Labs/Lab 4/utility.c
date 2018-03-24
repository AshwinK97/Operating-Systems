/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

// Define your utility functions here, you will likely need to add more...
int avail_mem = MEMORY;
memory_block head_block = NULL;
resources avail_resources = NULL;

memory_block create_memory_block() {
	memory_block block = malloc(sizeof(memory_block_t));
	block->next = NULL;
	block->previous = NULL;
	block->allocated = false;
	block->size = 0;
	block->offset = 0;

	return block;
}

void init_resources() {
  avail_resources = malloc(sizeof(resources_t));

  avail_resources->printers = 2;
  avail_resources->scanners = 1;
  avail_resources->modems = 1;
  avail_resources->CD_drives = 2;
}

void print_resource_list(resources resource_list){
    printf("-----------------\n");
    printf("printers: %d\n", resource_list->printers);
    printf("scanners: %d\n", resource_list->scanners);
    printf("modems: %d\n", resource_list->modems);
    printf("CD_drives: %d\n", resource_list->CD_drives);
    printf("-----------------\n\n");
}

void print_process(node process){
    printf("-----------------\n");
    printf("pid: %d\n", process->pid);
    printf("status: %d\n", process->status);
    printf("arrival_time: %d\n", process->arrival_time);
    printf("priority: %d\n", process->priority);
    printf("processor_time: %d\n", process->processor_time);
    printf("size: %d\n", process->size);
    print_resource_list(process->resource_list);
    printf("-----------------\n\n");
}

void print_memory_block(memory_block block){
    printf("-----------------\n");
    printf("offset: %d\n", block->offset);
    printf("size: %d\n", block->size);
    printf("allocated: %d\n", block->allocated);
    printf("-----------------\n\n");
}

void print_memory(){
  int block_num = 1;
  memory_block block = head_block;
  
  while(block != NULL){
    printf("-----------------\n");
    printf("Block %d\n", block_num);
    print_memory_block(block);
    block = block->next;
    block_num++;
  }
}

void free_mem(memory_block block){
  if(block == NULL)
    return;
  
  block->allocated = false;
  avail_mem = avail_mem + block->size;
  
  // Merge with next block if empty
  if(block->previous != NULL && !block->previous->allocated){
    merge_blocks(block->previous, block);
    block = block->previous;
  }
  
  // Merge with previous block if empty
  // Move block up, allowing for fewer gaps
  if(block->next != NULL && !block->next->allocated){
    merge_blocks(block, block->next);
  }
}

void merge_blocks(memory_block front, memory_block back){
  if(front == NULL || back == NULL)
    return;
  
  front->next = back->next;
  
  if(back->next != NULL)
    back->next->previous = front;
  
  front->size = front->size + back->size;
  free(back);
  back = NULL;
}

memory_block alloc_mem(int size)
{
  // First-Fit
  // Init memory block if memory has not been used
  if(avail_mem == MEMORY && head_block == NULL){
    head_block = create_memory_block();
    head_block->size = MEMORY;
    head_block->offset = 0;
  }

  // Not enough memory to allocate process
  if(size > avail_mem)
    return NULL;
  
  // Init placeholders for variables
  memory_block block = head_block;
  memory_block memory = NULL;

  // Loop through memory until an open mem block is found that can fit the process
  while(block != NULL && ((!block->allocated && (size > block->size)) || block->allocated)){
    
    // If the current block offset + size is past the memory limit
    // Return NULL; end of memory found
    if((block->offset + block->size) >= MEMORY)
      return NULL;
    
    block = block->next;
  }

  if(block != NULL){
    if(!block->allocated && block->size > size) {
      // Split the block into 2 parts if block size is bigger than process size
      split_block(block, size);
			memory = block;
			memory->allocated = true;
			avail_mem -= size;
		} else { 
      // Else block size is equal to process size, no need to split
			memory = block;
			memory->allocated = true;
			avail_mem -= memory->size;
		}
  }

  return memory;
}

memory_block split_block(memory_block block, int size){
  if (block == NULL)
    return NULL;
  
  // Save Main block size before modifications
  int main_block_size = block->size;

  // Remap block size to process size and store empty memory as new block
  block->size = size;
  memory_block new_block = NULL;

  if(size < main_block_size){
    new_block = create_memory_block();
    new_block->next = block->next;
    new_block->previous = block;
    new_block->allocated = false;
    new_block->size = main_block_size - size;
    new_block->offset = block->offset + size;

    block->next = new_block;
  }

  return new_block;
}

bool resourcesAvailable(resources resource_list){
  return ((avail_resources->printers >= resource_list->printers) && (avail_resources->scanners >= resource_list->scanners) && (avail_resources->modems >= resource_list->modems) && (avail_resources->CD_drives >= resource_list->CD_drives));
}

bool alloc_resources(resources resource_list){
  if (!resourcesAvailable(resource_list))
    return false;
  
  avail_resources->printers -= resource_list->printers;
  avail_resources->scanners -= resource_list->scanners;
  avail_resources->modems -= resource_list->modems;
  avail_resources->CD_drives -= resource_list->CD_drives;

  return true;
}

void free_resources(resources resource_list){
  avail_resources->printers += resource_list->printers;
  avail_resources->scanners += resource_list->scanners;
  avail_resources->modems += resource_list->modems;
  avail_resources->CD_drives += resource_list->CD_drives;
}