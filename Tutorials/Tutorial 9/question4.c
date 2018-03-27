#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

#define N 10

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

	print_matrix(a);
	print_matrix(b);

	// calculate matrix product ab
	//#pragma omp parallel for num_threads(100)
	//for (i=0; i<N; i++) {
	//	for (j=0; j<N; j++) {
	//		printf("%d from thread %d\n", a[i][j], omp_get_thread_num());
	//		printf("%d from thread %d\n", b[i][j], omp_get_thread_num());
	//	}
	//}
}
