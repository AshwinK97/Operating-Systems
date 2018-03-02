#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// constants
#define INFILE "puzzle.txt"

// mutex and barrier
pthread_mutex_t mutex;
pthread_barrier_t barrier;

// gloabl variables
int puzzle[10][10];

void *read_puzzle() {
	pthread_mutex_lock(&mutex); // lock mutex
	
	FILE *fp = fopen(INFILE, "r");
	int i, j;
	for (i=0; i<10; i++) {
		for (j=0; j<10; j++) {
			fscanf(fp, "%d", &puzzle[i][j]);
		}
	}
		fscanf(fp, "%d", &grades[i]);
	
	pthread_mutex_unlock(&mutex); // unlock mutex
	//pthread_barrier_wait(&barrier); // wait for barrier sync
	return NULL;
}

int main() {
	pthread_t read_thread;
	pthread_t c_threads[10]; // row threads
	pthread_t r_threads[10]; // col threads
	
	// initialize mutex and barrier
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("unable to initialize a mutex\n");
		return -1;
	}
	//if (pthread_barrier_init(&barrier, NULL, COUNT+1)) { // 11 threads to sync
	//	printf("unable to initialize a barrier\n");
	//	return -1;
	//}
	
	// create the read thread
	if (pthread_create(&read_thread, NULL, &read_grades, NULL)) {
		printf("failed to create read thred\n");
		return -1;
	}

	// create the write threads
	//int i;
	//for (i=0; i<COUNT; i++) {
	//	if (pthread_create(&w_threads[i], NULL, &save_bellcurve, (void *)(&i))) {
	//		printf("failed to create write thread %d\n", i);
	//		return -1;
	//	}
	//}

	// wait for threads to exit before terminating
	if (pthread_join(puzzle_thread, NULL)) {
		printf("failed to join puzzle thread\n");
		return -1;
	}
	//for (i=0; i<COUNT; i++) {
	//	if (pthread_join(w_threads[i], NULL)) {
	//		printf("failed to join write thread %d\n", i);
	//		return -1;
	//	}
	//}
	
	// free resources
	//pthread_barrier_destroy(&barrier);
	//pthread_mutex_destroy(&mutex);
	
	return 0;
}
