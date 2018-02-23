#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define COUNT 5

struct student {
	char name[20];
	int student_id;
	int grade;
};

void *bellcurve(void *args) {
	struct student *s = args;
	printf("Name: %s  id: %d \nBellcurved grade: %f\n", s->name, s->student_id, (float)(s->grade)*1.5);
	return NULL;
}

int main() {
	struct student students[COUNT];
	pthread_t threads[COUNT];

	// get inputs
	int i;
	for (i=0; i<COUNT; i++) {
		printf("Enter student %d name: ", i);
		scanf("%s", students[i].name);
		
		printf("Enter student %d id: ", i);
		scanf("%d", &students[i].student_id);

		printf("Enter student %d grade: ", i);
		scanf("%d", &students[i].grade);
		printf("\n");
	}

	// apply bell curves
	for (i=0; i<COUNT; i++) {
		if (pthread_create(&threads[i], NULL, &bellcurve, &students[i])) {
			printf("failed to create thread %d\n", i);
			return -1;
		}
	}

	//join last thread
	if (pthread_join(threads[COUNT-1], NULL)) {
		printf("Could not join thread %d\n", i);
		return -1;
	}

	return 0;
}
