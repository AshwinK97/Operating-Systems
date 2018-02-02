#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// define student structure
typedef struct student {
	int student_id;
	int age;
	int start_year;
} student_t;

void save_student(student_t *stu) {
	// open students.txt in append mode
	FILE *f = fopen("students.txt", "a");
	fprintf(f, "%d,%d,%d\n", stu->student_id, stu->age, stu->start_year);
	fclose(f);
}

int main() {
	// allocate student structure
	student_t *stu = NULL;
	stu = malloc(sizeof(student_t));
	
	// get inputs
	printf("Enter your student id: ");
	scanf("%d", &stu->student_id);	
	printf("Enter your age: ");
	scanf("%d", &stu->age);
	printf("Enter your start year at UOIT: ");
	scanf("%d", &stu->start_year);

	// write to file and free memory
	save_student(stu);
	free(stu);
}
