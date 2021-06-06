#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>

#include "utils.h"

int parse_arg(char *arg) {
    unsigned long n = 0;
    char *endptr;

    n = strtoul(arg, &endptr, 10);

    if (errno != 0) {
		perror("strtoul");
		return EXIT_FAILURE;
	}

    if (endptr == arg) {
        fprintf(stderr, "Failed to parse command line argument as number: %s\n", arg);
        return EXIT_FAILURE;
    }

    // clamp to int
    if (n > INT_MAX)
        return INT_MAX;
    else
        return n;
}

double walltime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    double secs = (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
    return secs;
}

void print_results(int N, int T, double time) {
    printf("Size: %d; Iterations: %d; Time: %.9f s\n", N, T, time);
}
