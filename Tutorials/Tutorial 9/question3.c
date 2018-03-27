#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

#define N 100000000

int main () {
	clock_t start;
	srand(time(NULL));
	int x[N];
	double snorm = 0, pnorm = 0;
	long int i;

	// generate random numbers
	for (i=0; i<N; i++)
		x[i] = rand();

	// serial loop
	start = clock();
	for (i=0; i<N; i++)
		snorm += fabs(x[i]);
	printf("Serial loop elapsed time: %.6f\n", (double)(clock() - start)/CLOCKS_PER_SEC);	
	printf("Serial norm = %f\n", snorm);

	// parallel loop
	start = clock();
	#pragma omp parallel for num_threads(10) reduction(+:pnorm)
	for (i=0; i<N; i++)
		pnorm += fabs(x[i]);
	printf("Parallel loop elapsed time: %.6f\n", (double)(clock() - start)/CLOCKS_PER_SEC);
	printf("Parallel norm = %f\n", pnorm);
}
