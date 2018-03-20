#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

int main (int argc, char *argv[]) {

	// Declare init variables
	double x = 0; // Watch out for race conditions!
	int thread_num, nthreads = atoi(argv[1]);
	int n = 1000000;
	double y[n];
	double dx = (1/(n+1));
	printf("dx: %d\n", dx);
	#ifdef _OPENMP
	omp_set_num_threads(nthreads);
	#endif
	#pragma omp parallel for private(x)

	for (int i = 0; i < n; ++i) {
		x = i+dx;
		#pragma omp critical {
			#ifdef _OPENMP
			y[i] = exp(x) * cos(x) * sin(x) * sqrt(5*x + 6.0);
			printf("%d: y=%f\n", i, y[i]);
			#endif
		}
	}
}
