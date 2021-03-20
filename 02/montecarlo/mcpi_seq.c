#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const unsigned long ITERATIONS = 500000000;

int main(int argc, char* argv[]) {
    unsigned long n = ITERATIONS;

    unsigned int state = 0;

    // try to read a number from the command line
    if (argc == 2) {
        unsigned long m = strtoul(argv[1], NULL, 10);
        if (m != 0) {
            n = m;
        }
    }

    struct timespec start_ts, end_ts;
    clock_gettime(CLOCK_REALTIME, &start_ts);

    unsigned long contained = 0;
    for (unsigned long i = 0; i < n; i++) {
        double x = (double) rand_r(&state) / RAND_MAX;
        double y = (double) rand_r(&state) / RAND_MAX;

        // sqrt calculation is superfluous for the less-than-1 comparison
        if (x*x + y*y < 1)
            contained++;
    }

    double pi = 4 * (double) contained / n;

    clock_gettime(CLOCK_REALTIME, &end_ts);

    double start_time = (double) start_ts.tv_sec + (double) start_ts.tv_nsec * 1e-9;
    double end_time = (double) end_ts.tv_sec + (double) end_ts.tv_nsec * 1e-9;

    printf("Iterations: %ld; pi: %.6lf; time: %.5lf\n", n, pi, end_time - start_time);

    return EXIT_SUCCESS;
}
