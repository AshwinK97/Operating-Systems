#include <stdio.h>
#include <omp.h>
int main ()
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;
	// will keep the following line if _OPENMP macro is defined.
	// omp_set_num_threads specifies number of threads used by subsequent parallel sections
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");

	// used to define a parallel section
    #pragma omp parallel
    {
		// used to define a critical section, which should run mutually exclusively, meaning by
		// only 1 thread at a time.
        #pragma omp critical
        {
            thread_num = omp_get_thread_num();
			// The following code will only exist if _OPENMP macro was defined during compilation
			// increments counter in thread safe manner, which will total to the number of threads
			// that run it.
            #ifdef _OPENMP
            num += 1; // THREAD SAFE INCREMENT
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}
