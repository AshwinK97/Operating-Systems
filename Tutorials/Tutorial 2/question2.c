#include <stdlib.h>
#include <stdio.h>

int main() {
	float ar[] = {1.2, 5.5, 2.1, 3.3, 3.3};
	
	int i;
	for (i=1; i<5; i++) { // start at 1 because no numbers before element 0
		if (ar[i] > ar[i-1])
			printf("greater than\n");
		else if (ar[i] < ar[i-1])
			printf("less than\n");
		else
			printf("the same\n");
	}
}
