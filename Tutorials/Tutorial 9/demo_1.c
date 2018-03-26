#include <stdio.h>
#include <omp.h>
int main ()
{
    printf("This statement will always print.\n");
	// this preprocessor will only allow the following print statement to remain in the code
	// if the macro _OPENMP exists. This occurs of the program is compiled with -fopenmp flag
    #ifdef _OPENMP
    printf("This statement will only print when compiled with \"-fopenmp\"\n");
    #endif
    return 0;
}
