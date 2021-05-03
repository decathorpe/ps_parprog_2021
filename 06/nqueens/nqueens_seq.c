#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

// get wall time in seconds
double walltime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    double secs = (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
    return secs;
}

int solutions(long n, char board[n][n], long placed) {
    if (placed == n)
        return 1;

    int sols = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j])
                return 0;

            // check row and column
            for (int k = 0; k < n; k++) {
                if (board[i][k])
                    return 0;
                if (board[k][j])
                    return 0;
            }

            // TODO: check diagonals

            char (*new)[n] = malloc(n*n * sizeof(char));
            memcpy(new, board, n*n*sizeof(char));

            new[i][j] = 1;

            sols += solutions(n, new, placed + 1);

            free(new);
        }
    }

    return sols;
}

int main(int argc, char* argv[]) {
    long n = 0;
    char *endptr;

    // try to read a number from the command line
    if (argc != 2) {
        fprintf(stderr, "Too few arguments.\n");
        return EXIT_FAILURE;
    }

    n = strtol(argv[1], &endptr, 10);

    if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}

    if (endptr == argv[1]) {
        fprintf(stderr, "Failed to parse command line argument as number: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char (*board)[n] = calloc(n*n, sizeof(char));

    // -----------------------------------------------------------------------

    double start_time = walltime();

    long sols = solutions(n, board, 0);

    double end_time = walltime();

    // -----------------------------------------------------------------------

    printf("result: %ld, time: %2.9f seconds\n", sols, end_time - start_time);

    free(board);

    return EXIT_SUCCESS;
}
