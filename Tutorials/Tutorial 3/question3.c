#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// define student structure
typedef struct student {
	char student_id[25];
	char age[25];
	char start_year[25];
} student_t;

void save_student(student_t *stu) {
	// open students.txt in append mode
	FILE *f = fopen("students.txt", "a");
	
	// string buffer for line to write
	char str[50];
	strcpy(str, stu->student_id);
	strcat(str, ",");
	strcat(str, stu->age);
	strcat(str, ",");
	strcat(str, stu->start_year);
    strcat(str, "\n");

	// write student info to file
	fputs(str, f);
	fclose(f);
}

int main() {
	// allocate student structure
	student_t *stu = NULL;
	stu = malloc(sizeof(student_t));
	
	// get inputs
	printf("Enter your student id: ");
	scanf("%s", stu->student_id);	
	printf("Enter your age: ");
	scanf("%s", stu->age);
	printf("Enter your start year at UOIT: ");
	scanf("%s", stu->start_year);

	// write to file and free memory
	save_student(stu);
	free(stu);
}
