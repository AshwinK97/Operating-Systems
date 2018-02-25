#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define COUNT 10

pthread_mutex_t mutex;
int total_grade = 0;

void *class_total(void *args) {
	pthread_mutex_lock(&mutex);
	int *grade = args;
	total_grade += *grade;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main() {
	int grades[COUNT];
	pthread_t threads[COUNT];

	// get inputs
	int i;
	for (i=0; i<COUNT; i++) {
		printf("Enter grade %d: ", i);
		scanf("%d", &grades[i]);
	}
	
	// initialize mutex
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("unable to initialize a mutex\n");
		return -1;
	}

	// create threads
	for (i=0; i<COUNT; i++) {
		if (pthread_create(&threads[i], NULL, &class_total, &grades[i])) {
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
	
	// print class total
	printf("The class total: %d\n", total_grade);
	
	// free resources
	pthread_mutex_destroy(&mutex);

	return 0;
}
