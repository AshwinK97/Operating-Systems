#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	char fname[25];
	int age=0, height=0;

	printf("Enter your first name: ");
	scanf("%s", fname);

	printf("Enter your age: ");
	scanf("%d", &age);

	printf("Enter your height (cm): ");
	scanf("%d", &height);

	printf("Name: %s\nAge: %d\nHeight: %dcm\n", fname, age, height);
}
