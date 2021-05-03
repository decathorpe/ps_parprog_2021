#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <omp.h>

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

    // INIT

    // -----------------------------------------------------------------------

    double start_time = omp_get_wtime();

    // WORK

    double end_time = omp_get_wtime();

    // -----------------------------------------------------------------------

    // printf("result: %d, time: %2.9f seconds\n", b[n-1], end_time - start_time);

    // CLEANUP

    return EXIT_SUCCESS;
}
