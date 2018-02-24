#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define COUNT 5

void *bellcurve(void *args) {
	int *grade = args;
	printf("Bellcurved grade: %f\n", (float)(*grade)*1.5);
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

	// create threads to apply bellcurves
	for (i=0; i<COUNT; i++) {
		if (pthread_create(&threads[i], NULL, &bellcurve, &grades[i])) {
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

	return 0;
}
