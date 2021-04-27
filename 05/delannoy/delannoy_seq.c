#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>

// get wall time in seconds
double walltime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    double secs = (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
    return secs;
}

__uint128_t factorial(uint64_t n) {
    __uint128_t prod = 1;

    for (uint64_t i = 1; i <= n; i++) {
        prod *= i;
    }

    return prod;
}

uint64_t bincoeff(uint64_t n, uint64_t k) {
    return factorial(n) / factorial(k) / factorial(n - k);
}

uint64_t delannoy(uint64_t m, uint64_t n) {
    uint64_t K = (m < n) ? m : n;

    uint64_t sum = 0;
    for (uint64_t k = 0; k <= K; k++) {
        sum += bincoeff(m, k) * bincoeff(n, k) * (1 << k);
    }

    return sum;
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

    if (n > 27) {
        fprintf(stderr, "Results for n > 27 are wrong (integer overflows).\n");
        return EXIT_FAILURE;
    }

    // -----------------------------------------------------------------------

    double start_time = walltime();

    unsigned long d = delannoy(n, n);

    double end_time = walltime();

    // -----------------------------------------------------------------------

    printf("result: %lu, time: %2.9f seconds\n", d, end_time - start_time);

    return EXIT_SUCCESS;
}
