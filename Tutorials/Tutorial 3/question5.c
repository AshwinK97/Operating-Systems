#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct grade {
	int student_id;
	int mark;
} grade_t;

// calculate the standard deviation
float sd_calc(grade_t grades[], int num_students, int sum) {

	// declare mean, std dev and counter
	float mean = sum/num_students, sd = 0;
	int i;

	// iterate grades and add to std dev 
	for (i=0; i<num_students; i++)
		sd += pow((float)grades[i].mark - mean, 2);
	
	// return std dev as float
	return sqrt(sd/num_students);
}

// record grades and get statistics
void grade_students(grade_t grades[], int num_students) {
	
	// open file in write mode, delare sum and loop counter
	FILE *f = fopen("grades.txt", "w");
	int i, sum = 0;
	
	// iterate through each grade struct
	for(i=0; i<num_students; i++) {
		// add marks to grade
		sum += grades[i].mark;
		// write string to file as <student_id>,<mark>
		fprintf(f, "%d,%d\n", grades[i].student_id, grades[i].mark);
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
	int num_students;
	
	// get professor's name and number of students
	printf("Enter professor name: ");
	scanf("%s", professor);
	printf("Enter number of students: ");
	scanf("%d", &num_students);

	// allocate grades array to be #ofstudents*sizeofgrade
	grade_t *grades = (grade_t *) malloc(num_students * sizeof(grade_t));

	// getthe student's grades
	int i;
	for (i=0; i<num_students; i++) {	
		printf("Student %d:\n", i);
		printf("id: ");
		scanf("%d", &grades[i].student_id);
		printf("mark: ");
		scanf("%d", &grades[i].mark);
	}

	// write the student's grades
	grade_students(grades, num_students);

	// free memory
	free(professor);
	free(grades);
}
