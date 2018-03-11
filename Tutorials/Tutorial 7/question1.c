#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INFILE "processes.txt"

struct proc {
	char name[256];
	int priority;
	int pid;
	int runtime;
};

struct queue {
	struct proc process;
	struct queue *next;
};

void push(struct queue *head, struct proc new_process) {
	struct queue *current = head;
	struct proc process = new_process;

	// find the next available space
	while(current->next != NULL)
		current = current->next;
	
	current->next = malloc(sizeof(struct queue));
	current->next->process = process;
	current->next->next = NULL;
}

void print_process(struct proc *print_process) {
	struct proc* process = print_process;

	printf("Name: %s\n", process->name);
	printf("pid: %d\n", process->pid);
	printf("priority: %d\n", process->priority);
	printf("runtime: %d\n", process->runtime);
	printf("%s\n\n", "-----------------");
}

void print_list(struct queue *head) {
	struct queue* current = head;

	while(current->next != NULL) {
		struct proc process = current->process;
		print_process(&process);
		current = current->next;
	}
}

void read_file(struct queue *head) {
	FILE *fp = fopen(INFILE, "r");
	char line[255];
	char *token;
	struct proc *new_process;

	while(fgets(line, sizeof(line), fp) != NULL) {	

		// allocate new proc struct
		new_process = malloc(sizeof(struct proc));
		
		// get name
		token = strtok(line, ",");
		strcpy(new_process->name, token);
		
		// get priority
		token = strtok(NULL, ",");
		sscanf(token, "%d", &new_process->priority);

		// get pid
		token = strtok(NULL, ",");
		sscanf(token, "%d", &new_process->pid);

		// get runtime
		token = strtok(NULL, "\n");
		sscanf(token, "%d", &new_process->runtime);
		
		// add to end of linked list
		push(head, *new_process);
	}
}

int main(void) {
	struct queue *head = NULL;
	head = malloc(sizeof(struct queue));
	head->next = NULL;

	read_file(head);
	print_list(head);

	return 0;
}
