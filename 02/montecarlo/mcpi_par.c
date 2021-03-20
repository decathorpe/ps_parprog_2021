#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

const unsigned long ITERATIONS = 500000000;
const unsigned long THREADS    = 1;

typedef struct {
    long chunk_size;
    long count;
} thread_data;

void *worker_thread(void *arg) {
    thread_data *data = (thread_data *) arg;

    // initialize thread-local random number generator state
    // with ... something thread-specific, I guess?
    unsigned int state = pthread_self();

    long contained = 0;
    for (long i = 0; i < data->chunk_size; i++) {
        double x = (double) rand_r(&state) / RAND_MAX;
        double y = (double) rand_r(&state) / RAND_MAX;

        // sqrt calculation is superfluous for the less-than-1 comparison
        if (x*x + y*y < 1)
            contained++;
    }

    data->count = contained;

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    unsigned long iterations = ITERATIONS;
    unsigned long threads = THREADS;

    // try to read a number of iterations from the command line
    if (argc >= 2) {
        unsigned long n = strtoul(argv[1], NULL, 10);
        if (n != 0)
            iterations = n;
    }

    // try to read a number of threads from the command line
    if (argc == 3) {
        unsigned long n = strtoul(argv[2], NULL, 10);
        if (n != 0)
            threads = n;
    }

    // split work into even chunks
    unsigned long chunk_size = iterations / threads;
    // if threads do not divide iterations evenly:
    // keep track of *actual* iterations here
    unsigned long iterations_actual = chunk_size * threads;

    if (iterations != iterations_actual)
        fprintf(stderr, "Threads do not divide iterations evenly.\n");

    thread_data *datas = calloc(threads, sizeof(thread_data));
    for (unsigned int i = 0; i < threads; i++) {
        datas[i].chunk_size = chunk_size;
        datas[i].count = 0;
    }

    pthread_t *thread_ids = calloc(threads, sizeof(pthread_t));

    struct timespec start_ts, end_ts;
    clock_gettime(CLOCK_REALTIME, &start_ts);

    // start threads and give them chunk_size
    for (unsigned int i = 0; i < threads; i++) {
        pthread_create(&thread_ids[i], NULL, worker_thread, (void *) &datas[i]);
    }

    // wait for threads to finish and collect results
    for (unsigned int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    // gather partial results from worker threads
    unsigned long contained = 0;
    for (unsigned int i = 0; i < threads; i++) {
        contained += datas[i].count;
    }

    double pi = 4 * (double) contained / iterations_actual;

    clock_gettime(CLOCK_REALTIME, &end_ts);

    free(thread_ids);
    free(datas);

    double start_time = (double) start_ts.tv_sec + (double) start_ts.tv_nsec * 1e-9;
    double end_time = (double) end_ts.tv_sec + (double) end_ts.tv_nsec * 1e-9;

    printf(
        "Iterations: %ld; threads: %ld; pi: %.6lf; time: %.5lf\n",
        iterations_actual, threads, pi, end_time - start_time
    );

    return EXIT_SUCCESS;
}
