#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "work.h"

#define BLOCK_SIZE ( (int) (64 / sizeof(double)) )

double work(int N, int T) {
    // clamp N to 2000, problem is too big otherwise
    if (N > 2000)
        N = 2000;

    // only execute stuff once, it takes long enough
    T = 1;

    // initial setup
    double (*a)[N] = malloc(N * N * sizeof(double));
    double (*b)[N] = malloc(N * N * sizeof(double));
    double (*c)[N] = malloc(N * N * sizeof(double));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = 1.0;
            b[i][j] = 1.0;
            c[i][j] = 1.0;
        }
    }

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        for (int ic = 0; ic < N; ic += BLOCK_SIZE) {
            for (int jc = 0; jc < N; jc += BLOCK_SIZE) {
                for (int i = ic; (i < ic + BLOCK_SIZE) && (ic < N); ++i) {
                    for (int j = jc; (j < jc + BLOCK_SIZE) && (j < N); ++j) {
                        for (int k = 0; k < N; ++k) {
                            c[i][j] = a[i][k] * b[k][j];
                        }
                    }
                }
            }
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%lf %lf %lf\n", a[N-1][N-1], b[N-1][N-1], c[N-1][N-1]);
    }

    // cleanup
    free(c);
    free(b);
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
