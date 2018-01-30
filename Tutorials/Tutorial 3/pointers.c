#include <stdlib.h>
#include <stdio.h>

/* prints pointer address and value */
void print_pointer(int *p) {
	printf("%p -> %d\n", (void *)p, *p);
}

int main() {
	/* make pointer and point to variable */
	int *p;
	int num = 20;
	p = &num;
	print_pointer(p);
	
	/* Change pointer address to another variable  */
	int num2 = 35;
	p = &num2;
	print_pointer(p);
	
	/* Change value at pointer address */
	*p += 1;
	print_pointer(p);
}
