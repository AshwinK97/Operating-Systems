#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

// constants
#define DIM 9
#define TOTAL 45
#define INFILE "solution.txt"

// mutex
pthread_mutex_t mutex;

// global variables
int puzzle[DIM][DIM];
int valid = 1;

void *read_puzzle() {
	pthread_mutex_lock(&mutex); // lock mutex

	FILE *fp = fopen(INFILE, "r");
	int i, j;
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++)
			fscanf(fp, "%d", &puzzle[i][j]);
	}

	pthread_mutex_unlock(&mutex); // unlock mutex

	return NULL;
}

void *row_check(void *arg) {
	int i, row = *((int*)arg); // convert pointer to int
	int sum = 0;

	for (i=0; i<DIM; i++) {
		sum += puzzle[row][i];
	}
	if (sum != TOTAL) {
		printf("Solution not valid\n");
		pthread_mutex_lock(&mutex); // lock mutex
		if (valid == 1)
			valid = 0;
		pthread_mutex_unlock(&mutex); // unlock mutex
	}
	pthread_exit(0);
}

void *col_check(void *arg) {
	int i, col = *((int*)arg); // convert pointer to int
	int sum = 0;

	for (i=0; i<DIM; i++) {
		sum += puzzle[i][col];
	}

	if (sum != TOTAL){
		printf("Solution not valid\n");
		pthread_mutex_lock(&mutex);
		if (valid == 1)
			valid = 0;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

void *box_check(void *arg) {
	int box = *((int*)arg); // convert pointer to int
	int sum = 0;

	int row = (int)(ceil(box - 3)) * 3;
	int col = (int)((box - 1) % 3) * 3;

	for (; row<row+3; row++) {
		for (; col<col+3; col++) {
			sum += puzzle[row][col];
		}
	}

	if (sum != TOTAL){
		printf("Solution not valid\n");
		pthread_mutex_lock(&mutex);
		if (valid == 1)
			valid = 0;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

void print_puzzle() {
	int i, j;
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++)
			printf("%d ", puzzle[i][j]);
		printf("\n");
	}
}

int main() {
	pthread_t read_thread;
	pthread_t r_threads[DIM]; // row threads
	pthread_t c_threads[DIM]; // col threads
	pthread_t b_threads[DIM]; // box threads
	int i;

	// initialize mutex and barrier
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("unable to initialize a mutex\n");
		return -1;
	}

	// create the read thread
	if (pthread_create(&read_thread, NULL, &read_puzzle, NULL)) {
		printf("failed to create read thread\n");
		return -1;
	}

	// pause execution until file is read
	if (pthread_join(read_thread, NULL)) {
		printf("failed to join read thread\n");
		return -1;
	}

	// create the row threads
	// for (i=0; i<DIM; i++) {
	// 	if (pthread_create(&r_threads[i], NULL, &row_check, &i)) {
	// 		printf("failed to create row thread %d\n", i);
	// 		return -1;
	// 	}
	// }
	//
	// // create the col threads
	// for (i=0; i<DIM; i++) {
	// 	if (pthread_create(&c_threads[i], NULL, &col_check, &i)) {
	// 		printf("failed to create col thread %d\n", i);
	// 		return -1;
	// 	}
	// }

	// create the box threads
	for (i=0; i<DIM; i++) {
		if (pthread_create(&b_threads[i], NULL, &box_check, &i)) {
			printf("failed to create row thread %d\n", i);
			return -1;
		}
	}

	// wait for check threads to exit before terminating
	// for (i=0; i<DIM; i++) {
	// 	if (pthread_join(r_threads[i], NULL)) {
	// 		printf("failed to join row thread %d\n", i);
	// 		return -1;
	// 	}
	// }
	// for (i=0; i<DIM; i++) {
	// 	if (pthread_join(c_threads[i], NULL)) {
	// 		printf("failed to join col thread %d\n", i);
	// 		return -1;
	// 	}
	// }
	for (i=0; i<DIM; i++) {
		if (pthread_join(b_threads[i], NULL)) {
			printf("failed to join box thread %d\n", i);
			return -1;
		}
	}

	// free resources
	pthread_mutex_destroy(&mutex);

	return 0;
}
