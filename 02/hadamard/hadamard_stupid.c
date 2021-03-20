#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const size_t DEFAULT_SIZE = 1000;

int main(int argc, char* argv[]) {
    size_t n = DEFAULT_SIZE;

    // try to read a number from the command line
    if (argc == 2) {
        long m = strtol(argv[1], NULL, 10);
        if (m != 0) {
            n = m;
        }
    }

    int32_t (*a)[n] = calloc(n * n, sizeof(int32_t));
    int32_t (*b)[n] = calloc(n * n, sizeof(int32_t));
    int32_t (*c)[n] = calloc(n * n, sizeof(int32_t));

    struct timespec start_ts, end_ts;
    clock_gettime(CLOCK_REALTIME, &start_ts);

    // hadamard product, algorithm 2
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    clock_gettime(CLOCK_REALTIME, &end_ts);

    double start_time = (double) start_ts.tv_sec + (double) start_ts.tv_nsec * 1e-9;
    double end_time = (double) end_ts.tv_sec + (double) end_ts.tv_nsec * 1e-9;

    printf("Matrix size: %ld; time: %2.5f seconds\n", n, end_time - start_time);

    free(c);
    free(b);
    free(a);

    return EXIT_SUCCESS;
}
