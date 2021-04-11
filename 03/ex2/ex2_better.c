#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
    do { \
        PERROR; \
        goto label; \
    } while (0)

void transpose(int n, int a[n][n], int b[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[j][i] = a[i][j];
        }
    }
}

unsigned long matmuladd(int n, int a[n][n], int b[n][n], int c[n][n]) {
    unsigned long result = 0;

    // temporarily allocate some more memory
    int (*bt)[n] = malloc(n * n * sizeof(int));
    if (bt == NULL) {
        PERROR;
        free(c); free(b); free(a);
        exit(EXIT_FAILURE);
    }

    // transpose matrix b for cache friendly read access
    transpose(n, b, bt);

    // matrix multiplication
    #pragma omp parallel for default(none) shared(n, a, bt, c)
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            for (long k = 0; k < n; ++k) {
                // note reversed indices: b[k][j] -> bt[j][k]
                c[i][j] += a[i][k] * bt[j][k];
            }
        }
    }

    // sum of matrix c
    #pragma omp parallel for default(none) shared(n, c) reduction(+: result)
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            result += c[i][j];
        }
    }

    // free temporary memory
    free(bt);

    return result;
}

int main(int argc, char **argv) {
    srand(7);
    errno = 0;

    // handle input
    if (argc != 2) {
        fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *str = argv[1];
    char *endptr;
    long n = strtol(str, &endptr, 0);

    if (errno != 0) {
        perror("strtol");
        return EXIT_FAILURE;
    }
    if (endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Error: matrix size must not be negative!\n");
        return EXIT_FAILURE;
    }

    // allocate memory:
    // a and b are initialized with values later
    int (*a)[n] = malloc(n * n * sizeof(int));
    if (a == NULL) {
        PERROR;
        return EXIT_FAILURE;
    }

    int (*b)[n] = malloc(n * n * sizeof(int));
    if (b == NULL) {
        PERROR;
        free(a);
        return EXIT_FAILURE;
    }

    // initialize result matrix c with zeroes;
    // initial values matter in the matrix multiplication algorithm
    int (*c)[n] = calloc(n * n, sizeof(int));
    if (c == NULL) {
        PERROR;
        free(b); free(a);
        return EXIT_FAILURE;
    }

    // fill matrices a and b with random numbers
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }

    unsigned long result = 0;

    // ========================================================================

    double start_time = omp_get_wtime();

    result = matmuladd(n, a, b, c);

    double end_time = omp_get_wtime();

    // ========================================================================

    printf("res: %lu, time: %2.5f seconds\n", result, end_time - start_time);

    // cleanup
    free(c);
    free(b);
    free(a);

    return EXIT_SUCCESS;
}