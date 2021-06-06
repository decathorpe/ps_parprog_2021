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

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        for (int i = 0; i < N; ++i) {
            if (N % 2) {
                a[i] = b[i] + 5;
            } else {
                a[i] = c[i] + 5;
            }
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%d %d %d\n", a[N-1], b[N-1], c[N-1]);
    }

    // cleanup
    free(c);
    free(b);
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
