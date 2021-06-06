#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "work.h"

double work(int N, int T) {
    // initial setup
    double *a = malloc(N * sizeof(double));

    for (int i = 0; i < N; ++i) {
        a[i] = 0.0;
    }

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        for (int i = 0; i < N; ++i) {
            a[i] *= hypot(0.3, 0.4);
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%lf\n", a[N-1]);
    }

    // cleanup
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
