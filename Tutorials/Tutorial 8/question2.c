#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define INFILE "processes_q2.txt"
#define MEMORY 1024

int avail_mem[1024];

struct proc {
	char name[256];
	int priority;
	int pid;
	int address;
	int memory;
	int runtime;
	bool suspended;
};

struct queue {
	struct proc process;
	struct queue *next;
};

void print_process(struct proc *process) {

	printf("name: %s\n", process->name);
	printf("priority: %d\n", process->priority);
	printf("pid: %d\n", process->pid);
	printf("address: %d\n", process->address);
	printf("memory: %d\n", process->memory);
	printf("runtime: %d\n", process->runtime);
	printf("%s\n\n", "-----------------");
}

void push(struct queue *head, struct proc new_process) {
	struct queue *current = head;
	struct proc process = new_process;

	// find the next available space
	while(current->next != NULL){
		print_process(&current->process);
		current = current->next;
	}
	
	current->next = malloc(sizeof(struct queue));
	current->next->process = process;
	current->next->next = NULL;
}

struct proc* pop(struct queue** head){
	struct proc* process_popped = NULL;
	struct queue* new_head = NULL;

	if(*head == NULL)
		return process_popped;
	
	new_head = (*head)->next;
	process_popped = &(*head)->process;

	free(*head);
	*head = new_head;

	return process_popped;
}

void print_list(struct queue *head) {
	struct queue* current = head;

	while(current != NULL) {
		struct proc process = current->process;
		print_process(&process);
		current = current->next;
	}
}

void read_file(struct queue *pri, struct queue *sec) {
	FILE *fp = fopen(INFILE, "r");
	char line[255];
	char *token;
	struct proc *process;

	while(fgets(line, sizeof(line), fp) != NULL) {
		// allocate new proc struct
		process = malloc(sizeof(struct proc));

		// get parent
		token = strtok(line, ",");
		strcpy(process->name, token);

		// get priority
		token = strtok(NULL, ",");
		sscanf(token, "%d", &process->priority);

		// get runtime
		token = strtok(NULL, ",");
		sscanf(token, "%d", &process->memory);

		// get runtime
		token = strtok(NULL, "\n");
		sscanf(token, "%d", &process->runtime);

		process->pid = 0;
		process->address = 0;

		if(process->priority == 0){
			push(pri, *process);
		} else {
			push(sec, *process);
		}
	}
}

int main() {
	avail_mem[0] = 0;

	// Priority Queue Init
	struct queue *priority_head = NULL;
	priority_head = malloc(sizeof(struct queue));
	priority_head->next = NULL;

	// Secondary Queue Init
	struct queue *secondary_head = NULL;
	secondary_head = malloc(sizeof(struct queue));
	secondary_head->next = NULL;

	read_file(priority_head, secondary_head);

	// Current process
	struct proc *current_process;

	while((current_process = pop(&priority_head)) != NULL){
	}
}
