#include <stdlib.h>
#include <stdio.h>

int main() {
	char str[] = "hello world";
	
	int i = 0;
	while (1) {
		if (str[i] == '\0') // check for null terminator
			break;
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}
