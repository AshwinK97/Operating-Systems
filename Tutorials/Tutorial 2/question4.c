#include <stdlib.h>
#include <stdio.h>

int main() {

	int i;
	for (i=1; i<=10; i++) {
		printf("%s ", (i%2==0) ? "even" : "odd");
	}
	printf("\n");
}
