#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "work.h"

double work(int N, int T) {
    // initial setup
    int *a = malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        a[i] = 1;
    }

    int min = 0;
    int sum = 0;

    double start_time = walltime();

    for (int t = 0; t < T; ++t) {
        // start work

        min = a[0];

        // split off a[0] from sum too
        sum = a[0];

        // merge two loops with identical bounds
        for (int i = 1; i < N; ++i) {
            min = (a[i] < min) ? a[i] : min;
            sum += a[i];
        }

        // end work
    }

    double end_time = walltime();

    // prevent over-optimization
    if (T == 1000) {
        fprintf(stderr, "%d\n", a[N-1]);
        fprintf(stderr, "%d %d\n", min, sum);
    }

    // cleanup
    free(a);

    double time = end_time - start_time;
    print_results(N, T, time);

    return time;
}
