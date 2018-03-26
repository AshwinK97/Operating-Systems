#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

double calculate(int num)
{
		double result = (exp(num) * cos(num) * sin(num) * sqrt(5 * num + 6.0));
		return result;
}

int main (int argc, char* argv[])
{
		double x = 0; // Watch out for race conditions!
		int n = 100000;
		double y[n];
		double dx = 1 / (n+1);
		int thread_num, nthreads = atoi(argv[1]);
		#ifdef _OPENMP
		omp_set_num_threads(nthreads);
		#endif
		printf("Testing OpenMP, you should see each thread print...\n");
		#pragma omp parallel for private(x)
		for (int i = 0; i < n; ++i)
		{
				x = i * dx;
				printf("\nx: %f, i: %d, dx: %f", x, i, dx);
				y[i] = calculate(x);
				#pragma omp critical
				{
					#ifdef _OPENMP
					thread_num = omp_get_thread_num();
					//printf("This thread = %d, num = %d, expensive = %f\n", thread_num, i, y[i]);
					#endif
				}
		}
}
