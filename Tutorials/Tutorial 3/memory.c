#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	char *text = (char*)malloc(5 * sizeof(char));
	strcpy(text, "Eric");
	printf("Our TA is %s\n", text);
}
