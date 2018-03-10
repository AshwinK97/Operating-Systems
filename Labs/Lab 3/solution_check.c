#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

// constants
#define DIM 9
#define TOTAL 45

// mutex
pthread_mutex_t mutex;

// global variables
int puzzle[DIM][DIM];
int valid = 1;

void print_puzzle() {
	int i, j;
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++)
			printf("%d ", puzzle[i][j]);
		printf("\n");
	}
}

void *read_puzzle() {
	pthread_mutex_lock(&mutex); // lock mutex

	(FILE *fp = fopen(argv[1], "r") == 0)
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
		if (valid == 0) {
			pthread_exit(0);
		}
		sum += puzzle[row][i];
	}
	if (sum != TOTAL) {
		printf("Row not valid: %d\n", row);
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
		if (valid == 0) {
			pthread_exit(0);
		}
		sum += puzzle[i][col];
	}
	if (sum != TOTAL){
		printf("Column not valid: %d\n", col);
		pthread_mutex_lock(&mutex);
		if (valid == 1)
			valid = 0;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

void *box_check() {
	int row, col, sum;

	for (row=1; row<=DIM; row+=3) {
		for (col=1; col<=DIM; col+=3) {
			if (valid == 0) {
				pthread_exit(0);
			}

			sum = 0;
			sum += puzzle[row-1][col-1] + puzzle[row-1][col] + puzzle[row-1][col+1];
			sum += puzzle[row][col-1] + puzzle[row][col] + puzzle[row][col+1];
			sum += puzzle[row+1][col-1] + puzzle[row+1][col] + puzzle[row+1][col+1];

			if (sum != TOTAL){
				printf("Block (%d, %d) not valid\n", row-1, col-1);
				pthread_mutex_lock(&mutex);
				if (valid == 1)
					valid = 0;
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	pthread_exit(0);
}

int main() {
	pthread_t read_thread;    // read thread
	pthread_t r_threads[DIM]; // row threads
	pthread_t c_threads[DIM]; // col threads
	pthread_t b_thread;       // box thread

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
	int ri;
	for (ri=0; ri<DIM; ri++) {
		int rtemp = ri;
		if (pthread_create(&r_threads[ri], NULL, &row_check, &rtemp)) {
			printf("failed to create row thread %d\n", rtemp);
			return -1;
		}
	}

	// create the col threads
	int ci;
	for (ci=0; ci<DIM; ci++) {
		int ctemp = ci;
		if (pthread_create(&c_threads[ci], NULL, &col_check, &ctemp)) {
			printf("failed to create col thread %d\n", ctemp);
			return -1;
		}
	}

	// create the box thread
	if (pthread_create(&b_thread, NULL, &box_check, NULL)) {
		printf("failed to create row thread \n");
		return -1;
	}

	// wait for check threads to exit before terminating
	int rj;
	for (rj=0; rj<DIM; rj++) {
		if (pthread_join(r_threads[rj], NULL)) {
			printf("failed to join row thread %d\n", rj);
			return -1;
		}
	}

	int cj;
	for (cj=0; cj<DIM; cj++) {
		if (pthread_join(c_threads[cj], NULL)) {
			printf("failed to join col thread %d\n", cj);
			return -1;
		}
	}


	if (pthread_join(b_thread, NULL)) {
		printf("failed to join box thread\n");
		return -1;
	}

	// free resources
	pthread_mutex_destroy(&mutex);

	if (valid == 1) {
		printf("%s\n", "Solution is valid\n");
	} else {
		printf("%s\n", "Solution is invalid\n");
	}

	return 0;
}
