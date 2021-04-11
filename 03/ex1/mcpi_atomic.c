#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

const unsigned long ITERATIONS = 500000000;

int main(int argc, char* argv[]) {
    unsigned long n = ITERATIONS;
    
    // try to read a number from the command line
    if (argc == 2) {
        unsigned long m = strtoul(argv[1], NULL, 10);
        if (m != 0) {
            n = m;
        }
    }

    unsigned long contained = 0;
    unsigned long iterations = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        // get semi-random RNG seed 
        unsigned int state = time(NULL) + omp_get_thread_num();
        unsigned int local_contained = 0;

        int num_threads = omp_get_num_threads();

        unsigned long chunk_size = n / num_threads;

        for (unsigned long i = 0; i < chunk_size; i++) {
            double x = (double) rand_r(&state) / RAND_MAX;
            double y = (double) rand_r(&state) / RAND_MAX;

            if (x*x + y*y < 1)
                local_contained++;
        }

        #pragma omp atomic
        contained += local_contained;
        #pragma omp atomic
        iterations += chunk_size;
    }

    double pi = 4 * (double) contained / iterations;

    double end_time = omp_get_wtime();

    printf("Iterations: %ld; pi: %.6lf; time: %.5lf\n", iterations, pi, end_time - start_time);

    return EXIT_SUCCESS;
}
