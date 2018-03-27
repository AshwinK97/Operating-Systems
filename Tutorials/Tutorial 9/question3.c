#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

#define N 100000

int main () {
	srand(time(NULL));
	int x[N];

	long int i;
	for (i=0; i<N; i++) {
		x[i] = rand();
		printf("%d, ", x[i]);
	}
	printf("\n");

	//#pragma omp parallel for private(x, tid) num_threads(nthreads)
	//for (long int i = 0; i < n; i++) {
	//	x = i * dx;
	//	tid = omp_get_thread_num();
	//	printf("thread %d -> x: %f, i: %ld, dx: %f\n", tid, x, i, dx);
	//	y[i] = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);
	//}
}
