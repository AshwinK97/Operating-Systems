#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main() {
	// allocate and zero initialize 256 chars for professor name
	char *professor = calloc(256, sizeof(char));
	int n;
	
	// get professor name and number of students
	printf("Enter your name: ");
	scanf("%s", professor);
	printf("Enter number of students: ");
	scanf("%d", &n);
	
	// allocate int array of size [n] for student_ids and grades
	int *student_ids = malloc(n*sizeof(int));
	int *grades = malloc(n*sizeof(int));

	// free memory
	free(professor);
	free(student_ids);
	free(grades);
}
