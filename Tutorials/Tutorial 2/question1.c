#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
	int ar[10]; // declare array
	srand(time(NULL)); // seed random number generator
	
	int i;
	for (i=0; i<10; i++) {
		ar[i] = rand()%10; // generate random number for each array element
		printf("%d ", ar[i]); // print the current array element
	}
	printf("\n"); // print line break
}
