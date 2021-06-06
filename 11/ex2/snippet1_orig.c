#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "work.h"

double work(int N, int T) {
    // make N odd
    if (!(N % 2))
        N++;

    // initial setup
    int *a = malloc(N * sizeof(int));
    int *b = malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        a[i] = 1;
        b[i] = 1;
    }

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        for (int i = 0; i < N - 1; ++i) {
            a[i] = b[i] + b[i + 1];
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%d %d\n", a[N-1], b[N-1]);
    }

    // cleanup
    free(b);
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
