#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

#define N 100

void print_matrix(int matrix[N][N]) {
	int i, j;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			printf("[%d]", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main () {
	srand(time(NULL));
	int a[N][N], b[N][N], c[N][N];
	int i, j, k;

	// generate random matrices
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			a[i][j] = rand()%10;
			b[i][j] = rand()%10;
		}
	}

	// calculate matrix product ab
	#pragma omp parallel for num_threads(N) private(i, j, k)
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			int sum = 0;
			for (k=0; k<N; k++) {
				sum += a[i][k]*b[k][j];
			}
			c[i][j] = sum;
		}
	}
	
	// print results
	printf("Matrix a:\n");
	print_matrix(a);
	printf("Matrix b:\n");
	print_matrix(b);
	printf("Matrix product ab:\n");
	print_matrix(c);
}
