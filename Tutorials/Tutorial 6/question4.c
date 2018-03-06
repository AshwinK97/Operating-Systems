#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NUMBERS 10
#define BUFFERLEN 5

// semaphore
sem_t semaphore;

// global variables
int buffer[BUFFERLEN] = {0, 0, 0, 0, 0};

void *produce(void *arg) {
	int *input = (int *)arg; // convert pointer arg to int array
	int i, bufferindex;
	srand(time(NULL));
	
	// loop through all numbers
	for (i=0; i<NUMBERS; i++) {
		
		// loop until a spot in the buffer is free
		for (bufferindex = 0; bufferindex<BUFFERLEN; bufferindex++) {

			// if we find an index that is empty, we fill it
			if (buffer[bufferindex] == 0) {
				sem_wait(&semaphore); // lock semaphore
				
				// produce number and place in buffer
				sleep(rand() % 3 + 1); // wait for 1-3 seconds
				buffer[bufferindex] = input[i];
				printf("Produced %d\n", buffer[bufferindex]);
				
				sem_post(&semaphore); // unlock semaphore
				break;
			}

			// if we reach last index, loop back to the first one
			if (bufferindex == 4)
				bufferindex = 0;
		}
	}

	pthread_exit(0);
}

void *consume() {
	int i, bufferindex;
	srand(time(NULL));

	// loop through all numbers
	for (i=0; i<NUMBERS; i++) {
		
		// loop until a spot in the buffer is occupied
		for (bufferindex = 0; bufferindex<BUFFERLEN; bufferindex++) {
			
			// if we find an index that isn't empty, we take it
			if (buffer[bufferindex] != 0) {
				sem_wait(&semaphore); // lock semaphore
				
				// consume number and free buffer
				sleep(rand() % 3 + 1); // wait for 1-3 seconds
				printf("Consumed %d\n", buffer[bufferindex]);
				buffer[bufferindex] = 0;

				sem_post(&semaphore); // unlock semaphore
				break;
			}

			// if  we reach last index, loop back to the first one
			if (bufferindex == 4)
				bufferindex = 0;
		}
	}

	pthread_exit(0);
}

int main() {
	pthread_t producer, consumer;
	int i, input[NUMBERS];

	// initialize semaphore for single access
	if (sem_init(&semaphore, 0, 1)) {
		printf("could not initialize semaphore\n");
		return -1;
	}
	
	// get input for array
	for (i=0; i<NUMBERS; i++) {
		printf("Enter number %d: ", i);
		scanf("%d", &input[i]);
	}
	
	// create producer and consumer threads
	if (pthread_create(&producer, NULL, &produce, &input)) {
		printf("failed to create producer thread\n");
		return -1;
	}
	if (pthread_create(&consumer, NULL, &consume, NULL)) {
		printf("failed to create consumer thread\n");
		return -1;
	}

	// wait for threads to exit before terminating
	if (pthread_join(producer, NULL)) {
		printf("failed to join producer thread \n");
		return -1;
	}
	if (pthread_join(consumer, NULL)) {
		printf("failed to join consumer thread \n");
		return -1;
	}

	// free resources
	sem_destroy(&semaphore);

	// print contents of buffer
	printf("buffer -> ");
	for (i=0; i<BUFFERLEN; i++)
		printf("%d ", buffer[i]);
	printf("\n");
}
