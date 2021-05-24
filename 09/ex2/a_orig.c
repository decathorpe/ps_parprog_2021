#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE (2*1000*1000*1000)

// get wall time in seconds
double walltime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    double secs = (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
    return secs;
}

int main(int argc, char* argv[]) {
    int n = SIZE;

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));

    // initialize y with valid doubles
    for (int i=0; i < n; i++) {
        y[i] = 1.0;
    }

    double start = walltime();

    // begin snippet

    double factor = 1;

    for (int i=0; i < n; i++) {
        x[i] = factor * y[i];
        factor = factor / 2;
    }

    // end snippet

    double end = walltime();

    printf("Size: %d; time: %2.5f s\n", n, end-start);

    // prevent compiler from optimizing too much
    if (argc > 1) {
        printf("%lf\n", x[argc]);
    }

    free(y);
    free(x);

    return EXIT_SUCCESS;
}
