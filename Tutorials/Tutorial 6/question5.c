#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

#define COUNT 5
#define FILE1 "numbers.txt"
#define FILE2 "sum.txt"

// semaphore
sem_t semaphore;

// global variables
int total_sum = 0;

int fact(int x) {
	if (x==0) return 1;
	return x * fact(x-1);
}

void *factorial(void *arg) {
	int input = *((int *)arg); // convert pointer arg to int
	int f = fact(input);
	printf("factorial %d = %d\n", input, f);

	sem_wait(&semaphore); // lock semaphore

	total_sum += f; // increment total_sum

	sem_post(&semaphore); // unlock semaphore

	pthread_exit(0);
}

int main() {
	pid_t pid;
	pthread_t threads[COUNT];
	FILE *fp;
	int i;

	// initialize semaphore for single access
	if (sem_init(&semaphore, 0, 1)) {
		printf("could not initialize semaphore\n");
		return -1;
	}
	
	// get input and write to file
	fp = fopen(FILE1, "w");
	int input;
	for (i=0; i<COUNT; i++) {
		printf("Enter number %d: ", i);
		scanf("%d", &input);
		fprintf(fp, "%d\n", input);
	}
	fclose(fp);
	
	// child process
	if ((pid = fork()) == 0) {
		fp = fopen(FILE1, "r");

		// read numbers and create threads
		int thread_buffer;
		for (i=0; i<COUNT; i++) {
			fscanf(fp, "%d\n", &thread_buffer);
			printf("thread_buffer %d = %d\n", i+1, thread_buffer);
			if (pthread_create(&threads[i], NULL, &factorial, &thread_buffer)) {
				printf("failed to create thread %d\n", i);
				return -1;
			}
		}
		fclose(fp);

		// wait for threads to exit before continuing
		for (i=0; i<COUNT; i++) {
			if (pthread_join(threads[i], NULL)) {
				printf("failed to join thread %d\n", i);
				return -1;
			}
		}

		// write total sum to file
		fp = fopen(FILE2, "w");
		fprintf(fp, "%d", total_sum);
		fclose(fp);
	}

	// parent process
	else {
		waitpid(pid, NULL, 0); // wait for child to exit
		
		// read sum file and print to screen
		int sum_buffer;
		fp = fopen(FILE2, "r");
		fscanf(fp, "%d", &sum_buffer);
		printf("total_sum = %d\n", sum_buffer);
	}

	// free resources
	sem_destroy(&semaphore);
}
