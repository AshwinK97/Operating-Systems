#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *hello_world() {
	srand(time(NULL));
	sleep(rand() % 4); // sleep for random time between 0-4s
	printf("hello world\n");
	return NULL;
}

void *goodbye() {
	srand(time(NULL));
	sleep(rand() % 4);
	printf("goodbye\n");
	return NULL;
}

int main() {
	pthread_t thread1, thread2;
	
	// create thread 1
	if (pthread_create(&thread1, NULL, &hello_world, NULL)) {
		printf("Could not create thread 1\n");
		return -1;
	}
	// create thread 2
	if (pthread_create(&thread2, NULL, &goodbye, NULL)) {
		printf("Could not create thread 2\n");
		return -1;
	}

	//join thread 1
	if (pthread_join(thread1, NULL)) {
		printf("Could not join thread 1\n");
		return -1;
	}
	// join thread 2
	if (pthread_join(thread2, NULL)) {
		printf("Could not create thread 2\n");
		return -1;
	}

	return 0;
}
