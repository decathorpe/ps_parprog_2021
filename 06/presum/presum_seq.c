#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>

// get wall time in seconds
double walltime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    double secs = (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
    return secs;
}

void prefix_sum(unsigned long n, int32_t a[n], int32_t b[n]) {
    b[0] = 0;

    for (unsigned long i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i - 1];
    }
}

void print_int32_array(size_t n, int32_t array[n], char *name) {
    if (n == 0) {
        printf("%s: []\n", name);
        return;
    }

    printf("%s: [", name);
    for (size_t i = 0; i < n-1; i++) {
        printf("%d, ", array[i]);
    }
    
    printf("%d", array[n-1]);

    printf("]\n");
}

int main(int argc, char* argv[]) {
    unsigned long n = 0;
    char *endptr;
    
    // try to read a number from the command line
    if (argc != 2) {
        fprintf(stderr, "Too few arguments.\n");
        return EXIT_FAILURE;
    }

    n = strtoul(argv[1], &endptr, 10);

    if (errno != 0) {
		perror("strtoul");
		return EXIT_FAILURE;
	}

    if (endptr == argv[1]) {
        fprintf(stderr, "Failed to parse command line argument as number: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    int32_t *a = malloc(n * sizeof(int32_t));

    if (a == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    for (unsigned int i = 0; i < n; i++) {
        a[i] = 1;
    }

    int32_t *b = malloc(n * sizeof(int32_t));

    if (b == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    // -----------------------------------------------------------------------

    double start_time = walltime();

    prefix_sum(n, a, b);

    double end_time = walltime();

    // -----------------------------------------------------------------------

    printf("result: %d, time: %2.9f seconds\n", b[n-1], end_time - start_time);
    
    free(b);
    free(a);

    return EXIT_SUCCESS;
}
