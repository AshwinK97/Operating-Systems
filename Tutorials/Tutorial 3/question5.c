#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct grade {
	int student_id;
	int mark;
} grade_t;

// calculate the standard deviation
float sd_calc(grade_t *grades[], int num_students, int sum) {

	// declare mean, std dev and counter
	float mean = sum/num_students, sd = 0;
	int i;

	// iterate grades and add to std dev 
	for (i=0; i<num_students; i++)
		sd += pow((float)grades[i]->mark - mean, 2);
	
	// return std dev as float
	return sqrt(sd/num_students);
}

// record grades and get statistics
void grade_students(grade_t *grades[], int num_students) {
	
	// open file in write mode, string buffer, sum and loop counter
	FILE *f = fopen("grades.txt", "w");
	int i, sum = 0;
	char *str[50];
	
	// iterate through each grade struct
	for(i=0; i<num_students; i++) {
		// add marks to grade
		sum += grades[i]->mark;
		// write string to file as <student_id>,<mark>
		fprintf(f, "%d,%d\n", grades[i]->student_id, grades[i]->mark);
	}
	
	// get mean and standard deviation
	float mean = sum/num_students;
	float sd = sd_calc(grades, num_students, sum);

	// write both to file
	fprintf(f, "Mean: %f\n", mean);
	fprintf(f, "Standard Deviation: %f\n", sd);
	
	fclose(f);
}

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
