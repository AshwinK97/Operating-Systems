#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printarray(int array[], int size) {
	int i;
	for (i=0; i<size; i++)
		printf("%d ", array[i]);
	printf("\n");
}

int main() {
	int list[100];
	FILE *f = fopen("question2.txt", "r");

	int i = 0;
	while (!feof(f)) {
		fscanf(f, "%d", &list[i]);
		i++;
	}
	fclose(f);
	
	printarray(list, i-1);
}
