#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define COUNT 5

// semaphore
sem_t semaphore;

// global variables
int moving_sum[5] = {0, 0, 0, 0, 0};

int factorial(int x) {
	if (x==1) return x;
	return x * factorial(x-1);
}

void *task(void *arg) {
	int *arr = (int *)arg; // convert pointer arg to int array
	int i = arr[0], input = arr[1]; // get i and input from array
	int fact = factorial(input); // calculate the factorial of input
	
	sem_wait(&semaphore); // lock semaphore
	
	if (i > 0 && moving_sum[i-1] > 0)
		moving_sum[i] = fact + moving_sum[i-1];
	else
		moving_sum[i] = fact;

	sem_post(&semaphore); // unlock semaphore
	pthread_exit(0);
}

int main() {
	pthread_t threads[COUNT];

	// initialize semaphore for single access
	if (sem_init(&semaphore, 0, 1)) {
		printf("could not initialize semaphore\n");
		return -1;
	}
	
	// get inputs and create threads
	int i, input, arg[2] = {0, 0};
	for (i=0; i<COUNT; i++) {
		
		// get input
		printf("Enter number %d: ", i);
		scanf("%d", &input);
		
		// set arguments
		arg[0] = i;
		arg[1] = input;
		
		// create thread and pass arguments
		if (pthread_create(&threads[i], NULL, &task, &arg)) {
			printf("failed to create thread %d\n", i);
			return -1;
		}
	}

	// wait for threads to exit before terminating
	for (i=0; i<COUNT; i++) {
		if (pthread_join(threads[i], NULL)) {
			printf("failed to join thread %d\n", i);
			return -1;
		}
	}
	
	// free resources
	sem_destroy(&semaphore);
	
	// print array
	for (i=0; i<COUNT; i++)
		printf("%d ", moving_sum[i]);
	printf("\n");
}
