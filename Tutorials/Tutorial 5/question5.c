#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// constants
#define COUNT 10
#define INFILE "grades.txt"
#define OUTFILE "bellcurve.txt"

// mutex and barrier
pthread_mutex_t mutex;
pthread_barrier_t barrier;

// gloabl variables
int grades[COUNT];
int total_grade = 0;
float total_bellcurve = 0;

void *save_bellcurve(void *arg) {
	pthread_barrier_wait(&barrier); // wait for barrier sync
	pthread_mutex_lock(&mutex); // lock mutex
	
	int *i = arg;
	total_grade += grades[*i];
	total_bellcurve += (float)grades[*i]*1.5;
	
	FILE *fp = fopen(OUTFILE, "a");
	fprintf(fp, "%f\n", (float)grades[*i]*1.5);

	pthread_mutex_unlock(&mutex); // unlock mutex
	return NULL;
}

void *read_grades() {
	pthread_mutex_lock(&mutex); // lock mutex
	
	FILE *fp = fopen(INFILE, "r");
	int i;
	for (i=0; i<COUNT; i++)
		fscanf(fp, "%d", &grades[i]);
	fclose(fp);

	pthread_mutex_unlock(&mutex); // unlock mutex
	pthread_barrier_wait(&barrier); // wait for barrier sync
	return NULL;
}

int main() {
	pthread_t r_thread;
	pthread_t w_threads[COUNT];
	
	// initialize mutex and barrier
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("unable to initialize a mutex\n");
		return -1;
	}
	if (pthread_barrier_init(&barrier, NULL, COUNT+1)) { // 11 threads to sync
		printf("unable to initialize a barrier\n");
		return -1;
	}
	
	// create the read thread
	if (pthread_create(&r_thread, NULL, &read_grades, NULL)) {
		printf("failed to create read thred\n");
		return -1;
	}

	// create the write threads
	int i;
	for (i=0; i<COUNT; i++) {
		if (pthread_create(&w_threads[i], NULL, &save_bellcurve, &i)) {
			printf("failed to create write thread %d\n", i);
			return -1;
		}
	}

	// wait for threads to exit before terminating
	if (pthread_join(r_thread, NULL)) {
		printf("failed to join read thread\n");
		return -1;
	}
	for (i=0; i<COUNT; i++) {
		if (pthread_join(w_threads[i], NULL)) {
			printf("failed to join write thread %d\n", i);
			return -1;
		}
	}
	
	// free resources
	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}
