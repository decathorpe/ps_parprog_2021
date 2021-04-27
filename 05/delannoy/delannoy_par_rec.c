#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <omp.h>

#define THRESHOLD 8

uint64_t delannoy_rec(uint64_t m, uint64_t n) {
    if ((m == 0) || (n == 0)) {
        return 1;
    }

    uint64_t a, b, c;

    #pragma omp task shared(a) final((m-1)<THRESHOLD || n<THRESHOLD)
    a = delannoy_rec(m-1, n);

    #pragma omp task shared(b) final((m-1)<THRESHOLD || (n-1)<THRESHOLD)
    b = delannoy_rec(m-1, n-1);

    if (m == n) {
        #pragma omp taskwait
        c = a;
    } else {
        #pragma omp task shared(c) final((m)<THRESHOLD || (n-1)<THRESHOLD)
        c = delannoy_rec(m, n-1);
    }

    #pragma omp taskwait

    uint64_t d = a + b + c;

    return d;
}

uint64_t delannoy(uint64_t m, uint64_t n) {
    uint64_t d = 0;

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            d = delannoy_rec(m, n);
        }
    }

    return d;
}

int main(int argc, char* argv[]) {
    unsigned long n = 0;
    char *endptr;
    
    // try to read a number from the command line
    if (argc != 2) {
        fprintf(stderr, "Too few arguments.\n");
        return EXIT_FAILURE;
    }

    n = strtoul(argv[1], &endptr, 10);

    if (errno != 0) {
		perror("strtoul");
		return EXIT_FAILURE;
	}

    if (endptr == argv[1]) {
        fprintf(stderr, "Failed to parse command line argument as number: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (n > 22) {
        fprintf(stderr, "The implementation is only verified to be correct for n < 23.\n");
    }

    // -----------------------------------------------------------------------

    double start_time = omp_get_wtime();

    unsigned long d = delannoy(n, n);

    double end_time = omp_get_wtime();

    // -----------------------------------------------------------------------

    printf("result: %lu, time: %2.9f seconds\n", d, end_time - start_time);

    return EXIT_SUCCESS;
}
