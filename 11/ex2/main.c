#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "utils.h"
#include "work.h"

#define DEFAULT_SIZE 100000
#define DEFAULT_ITER 100000

int main(int argc, char* argv[]) {
    int N = DEFAULT_SIZE;
    int T = DEFAULT_ITER;

    // try to read sizes from the command line
    if (argc == 3) {
        N = parse_arg(argv[1]);
        T = parse_arg(argv[2]);
    }

    // ---------------------------------

    work(N, T);

    // ---------------------------------

    return EXIT_SUCCESS;
}
