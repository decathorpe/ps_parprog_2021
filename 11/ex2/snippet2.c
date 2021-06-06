#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "work.h"

double work(int N, int T) {
    // initial setup
    int *a = malloc(N * sizeof(int));
    int *b = malloc(N * sizeof(int));
    int *c = malloc(N * sizeof(int));
    int *d = malloc(N * sizeof(int));
    int *e = malloc(N * sizeof(int));
    int *f = malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        a[i] = 1;
        b[i] = 1;
        c[i] = 1;
        d[i] = 1;
        e[i] = 1;
        f[i] = 1;
    }

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        for (int i = 1; i < N - 2; ++i) {
            b[i]     =     a[i - 1] + 1;
            c[i]     = 2 * a[i];
            d[i]     =     a[i + 1] + 2;
            e[i + 1] =     a[i + 2] + 3;
            f[i + 1] =     e[i] + 4;
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%d %d %d %d %d %d\n", a[N-1], b[N-1], c[N-1], d[N-1], e[N-1], f[N-1]);
    }

    // cleanup
    free(f);
    free(e);
    free(d);
    free(c);
    free(b);
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
