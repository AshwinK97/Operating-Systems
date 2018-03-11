#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INFILE "processes.txt"

struct proc{
  char name[256];
  int priority;
  int pid;
  int runtime;
};

struct queue{
  struct proc process;
  struct queue* next;
};

void read_file(char* file){
  FILE *file_pointer = fopen(file, "r");
  char* line = NULL;

  while(!feof(file_pointer)){
    sscanf(line, file, "%s");
    printf("%s\n", line);
    printf("%s\n", "-----------------");
  }
}

void push(struct queue* head, struct proc new_process){
  struct queue* current = head;
  struct proc process = new_process;

  while(current->next != NULL)
    current = current->next;
  
  current->next = malloc(sizeof(struct queue));
  current->next->process = process;
  current->next->next = NULL;
}

void print_process(struct proc* print_process){
  struct proc* process = print_process;

  printf("Name: %s\n", process->name);
  printf("pid: %d\n", process->pid);
  printf("priority: %d\n", process->priority);
  printf("runtime: %d\n", process->runtime);
  printf("%s\n\n", "-----------------");
}

void print_list(struct queue* head){
  struct queue* current = head;

  while(current->next != NULL){
    struct proc process = current->process;
    print_process(&process);
    current = current->next;
  }
}

int main(void){
  printf("%d", 1);
  struct queue* head = NULL;
  head = malloc(sizeof(struct queue));
  head->next = NULL;

  read_file(INFILE);
  //print_list(head);

  return 0;
}