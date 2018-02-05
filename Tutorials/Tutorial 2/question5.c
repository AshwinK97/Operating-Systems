#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// calculate the distance between 2 points
double euclid_dist(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
	int i;
	for (i=0; i<10; i++) {
		srand(time(NULL) + i);
		// random values from 0 to 100 for points
		int x1 = rand()%101, y1 = rand()%101, x2 = rand()%101, y2 = rand()%101;
		// print distance between 2 random points
		printf("V1=(%d, %d) V2=(%d, %d) D=%f\n", x1, y1, x2, y2, euclid_dist(x1, y1, x2, y2));
	}
}
