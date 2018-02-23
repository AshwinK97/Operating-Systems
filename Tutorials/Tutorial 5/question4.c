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

	// add to total
	for (i=0; i<COUNT; i++) {
		if (pthread_create(&threads[i], NULL, &class_total, &grades[i])) {
			printf("failed to create thread %d\n", i);
			return -1;
		}
	}

	//join last thread
	if (pthread_join(threads[COUNT-1], NULL)) {
		printf("failed to join thread %d\n", i);
		return -1;
	}

	printf("The class total: %d\n", total_grade);

	return 0;
}
