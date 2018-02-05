#include <stdlib.h>
#include <stdio.h>

int main() {

	int i;
	for (i=1; i<=10; i++)
		printf("%d: %s ", i, (i%2) ? "odd" : "even");
	printf("\n");
}
