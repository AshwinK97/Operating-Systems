#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define FNAME "calculations.txt"

int main (int argc, char* argv[]) {

	// check for arguments
	if (argc < 2) {
		printf("question1.o: number of threads not specified\n");
		return -1;
	}
	
	long int i, n = 100000000;
	double x, y, dx = 1 / ((double)n+1);
	int nthreads = atoi(argv[1]);
	
	// clear output file
	FILE *fp = fopen(FNAME, "w");
	fclose(fp);
	
	#pragma omp parallel for private(x, y) num_threads(nthreads)
	for (i=0; i<n; i++) {
		x = i * dx;
		y = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);
		if (i%1000000 == 0 && i>0) {
			#pragma omp critcal
			{
				fp = fopen(FNAME, "a");
				fprintf(fp, "i: %ld, x: %f, y: %f\n", i, x, y);
				fclose(fp);
			}
		}
	}
}
