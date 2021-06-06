#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "work.h"

double work(int N, int T) {
    // initial setup
    int *a = malloc(N * sizeof(int));
    int *b = malloc(N * sizeof(int));
    int *c = malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        a[i] = 1;
        b[i] = 1;
        c[i] = 1;
    }

    int sum_a = 0;
    int sum_b = 0;
    int sum_c = 0;

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        sum_a = 0;
        sum_b = 0;
        sum_c = 0;

        for (int i = 0; i < N; ++i) {
            sum_a += a[i];
            sum_b += b[i];
            sum_c += c[i];
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%d %d %d\n", a[N-1], b[N-1], c[N-1]);
        fprintf(stderr, "%d %d %d\n", sum_a, sum_b, sum_c);
    }

    // cleanup
    free(c);
    free(b);
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
