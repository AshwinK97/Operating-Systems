#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

int main (int argc, char* argv[]) {

	// check for arguments
	if (argc < 2) {
		printf("question1.o: number of threads not specified\n");
		return -1;
	}

	double x = 0;
	long int n = 100000000;
	double y[n];
	double dx = 1 / ((double)n+1);
	int tid;
	int nthreads = atoi(argv[1]);
	
	#pragma omp parallel for private(x, tid) num_threads(nthreads)
	for (long int i = 0; i < n; i++) {
		x = i * dx;
		tid = omp_get_thread_num();
		printf("thread %d -> x: %f, i: %ld, dx: %f\n", tid, x, i, dx);
		y[i] = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);
	}
}
