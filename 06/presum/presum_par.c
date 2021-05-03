#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <omp.h>

void prefix_sum(unsigned long n, int32_t a[n], int32_t b[n], int32_t a0) {
    b[0] = a0;

    for (unsigned long i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i - 1];
    }
}

void offset_sum(unsigned long n, int32_t a[n], int32_t offset) {
    for (unsigned long i = 0; i < n; i++) {
        a[i] = a[i] + offset;
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

    double start_time = omp_get_wtime();

    int thread_num;

    #pragma omp parallel
    {
        #pragma omp single
        {
            thread_num = omp_get_num_threads();
        }
    }

    int32_t *partial_sums = malloc(thread_num * sizeof(int32_t));

    if (partial_sums == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    #pragma omp parallel
    {
        int cur_thread = omp_get_thread_num();
        int chunk = cur_thread;

        unsigned long chunk_size = n / thread_num;
        unsigned long offset = chunk * chunk_size;

        // the last chunk might be slightly bigger if p does not divide n
        unsigned long chunk_size_last = chunk_size + (n % thread_num);
        unsigned long chunk_size_real = (thread_num - 1 == chunk) ? chunk_size_last : chunk_size;

        // calculate prefix sums for all chunks separately
        // get initial value of prefix sum
        int a0 = (offset == 0) ? 0 : a[offset - 1];

        prefix_sum(chunk_size_real, a + offset, b + offset, a0);
        partial_sums[chunk] = b[offset + chunk_size_real - 1];

        #pragma omp barrier

        // calculate sum of partial sums of all preceding chunks
        int32_t partial_sum = 0;
        for (int i = 0; i < chunk; i++) {
            partial_sum += partial_sums[i];
        }

        // offset sum in current chunk by sum of prededing chunks
        if (partial_sum != 0) {
            offset_sum(chunk_size_real, b + offset, partial_sum);
        }
    }

    free(partial_sums);

    double end_time = omp_get_wtime();

    // -----------------------------------------------------------------------

    printf("result: %d, time: %2.9f seconds\n", b[n-1], end_time - start_time);

    free(b);
    free(a);

    return EXIT_SUCCESS;
}
