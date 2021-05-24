#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define SIZE (2*1000*1000*1000)

int main(int argc, char* argv[]) {
    int n = SIZE;

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));

    // initialize y with valid doubles
    #pragma omp parallel for
    for (int i=0; i < n; i++) {
        y[i] = 1.0;
    }

    double start = omp_get_wtime();

    // begin optimized snippet

    #pragma omp parallel for default(none) shared(x, y, n)
    for (int i = 0; i < n; i++) {
        double factor = ldexp(1, -i);
        x[i] = factor * y[i];
    }

    // end optimized snippet

    double end = omp_get_wtime();

    printf("Size: %d; time: %2.5f s\n", n, end-start);

    // prevent compiler from optimizing too much
    if (argc > 1) {
        printf("%lf\n", x[argc]);
    }

    free(y);
    free(x);

    return EXIT_SUCCESS;
}
