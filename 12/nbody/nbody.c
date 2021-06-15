#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

// const float G = 6.67408E-11;
#define G ((float) 1.0f)
#define dt ((float) 0.01f)

int STEPS = 0;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    Vec3 position;
    Vec3 velocity;
} Point;

// uniformly distributed values between 0 and 1
float unif() {
    float r;

    // rand() function is not MT-safe
    #pragma omp critical
    {
        r = (float) rand() / (float) RAND_MAX;
    }

    return r;
}

// random, uniformly distributed vector in [-0.5, 0.5] * scale
void uniform_coordinate(Vec3 *vec, float scale) {
    vec->x = (unif() - 0.5f) * scale;
    vec->y = (unif() - 0.5f) * scale;
    vec->z = (unif() - 0.5f) * scale;
}

// length of a 3D vector
// with -ffast-math, CPU instructions for sqrt are used directly,
// instead of wrapped in a function call to libc
static inline float length(Vec3 *vec) {
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

// vector addition (outparam c)
static inline void addition(Vec3 *a, Vec3 *b, Vec3 *c) {
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    c->z = a->z + b->z;
}

// vector difference (outparam d)
static inline void difference(Vec3 *a, Vec3 *b, Vec3 *d) {
    d->x = a->x - b->x;
    d->y = a->y - b->y;
    d->z = a->z - b->z;
}

// vector scaled by factor (outparam b)
static inline void scale(Vec3 *a, Vec3 *b, float factor) {
    b->x = a->x * factor;
    b->y = a->y * factor;
    b->z = a->z * factor;
}

// generate points with uniformly distributed
// coordinates, velocities, and masses
void gen_uniform_points(int n, Point points[n], float masses[n]) {
    // try to match "first touch" on memory
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        // set random position between -25 and +25
        uniform_coordinate(&points[i].position, 50.0f);
        // set random velocity between -0.5 and +0.5
        uniform_coordinate(&points[i].velocity, 1.0f);
        // set random mass between 0 and 1
        masses[i] = unif();
    }
}

// with inlined vector operations, -ffast-math, and -O3,
// this function does contain *any* function calls
void update_points(int n, Point old[n], Point new[n], float masses[n]) {
    /*
     * F_ij = G * (m_i * m_j) / |r_j - r_i|^3 * (r_j - r_i)
     * https://de.wikipedia.org/wiki/Newtonsches_Gravitationsgesetz#Vektoriell
     *
     * for each point i:
     * - calculate all difference vectors for i != j: (r_j - r_i)
     * - calculate all scalars:     G * (m_i * m_j) / |r_j - r_i|^3
     * - scale difference vectors with scalars to obtiain force vector
     * - calculate sum of force vectors acting on point i
     * - update position according to current velocity
     * - update velocity according to acting total force
     */

    // loop body only reads from old[:] and masses[:],
    // and only writes to non-overlapping new[i]
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        Vec3 force = { 0.0f, 0.0f, 0.0f };

        // constant factor shared for all j
        float G_mass_i = G * masses[i];

        // splitting into two loops for j < i and i > j instead of checking i != j
        // in each iteration reduces branches and improves runtime by ~5%
        for (int j = 0; j < i; j++) {
            Vec3 ijforce;
            difference(&old[j].position, &old[i].position, &ijforce);

            float len = length(&ijforce);
            float factor = G_mass_i * masses[j] / (len * len * len);

            scale(&ijforce, &ijforce, factor);
            addition(&force, &ijforce, &force);
        }

        for (int j = i+1; j < n; j++) {
            Vec3 ijforce;
            difference(&old[j].position, &old[i].position, &ijforce);

            float len = length(&ijforce);
            float factor = G_mass_i * masses[j] / (len * len * len);
            
            scale(&ijforce, &ijforce, factor);
            addition(&force, &ijforce, &force);
        }

        Vec3 delta;
        // update point position
        // calculate position delta
        scale(&old[i].velocity, &delta, dt);
        // apply position delta
        addition(&old[i].position, &delta, &new[i].position);

        // update point velocity
        // calculate velocity delta
        scale(&force, &delta, dt / masses[i]);
        // apply velocity delta
        addition(&old[i].velocity, &delta, &new[i].velocity);
    }
}

// write [float, float, float] in JSON format
static inline void write_coordinate(FILE *fp, Point *point, char *end) {
    fprintf(fp, "    [%f, %f, %f]%s\n", point->position.x, point->position.y, point->position.z, end);
}

// write [coordinate, ... ] array in JSON format
void write_coordinates(FILE *fp, int n, Point points[n], char *end) {
    fprintf(fp, "  [\n");

    for (int i = 0; i < n-1; i++) {
        write_coordinate(fp, &points[i], ",");
    }

    // JSON does not allow trailing comma
    write_coordinate(fp, &points[n-1], "");

    fprintf(fp, "  ]%s\n", end);
}

void simulation(int iterations, int n, char *outfile) {
    Point *points = malloc(n * sizeof(Point));

    if (points == NULL) {
        fprintf(stderr, "Allocation problems.\n");
        exit(EXIT_FAILURE);
    }

    Point *buffer = malloc(n * sizeof(Point));

    if (buffer == NULL) {
        fprintf(stderr, "Allocation problems.\n");
        exit(EXIT_FAILURE);
    }

    float *masses = malloc(n * sizeof(float));

    if (masses == NULL) {
        fprintf(stderr, "Allocation problems.\n");
        exit(EXIT_FAILURE);
    }

    gen_uniform_points(n, points, masses);

    FILE *fp = NULL;
    char *end = ",";

    if (STEPS) {
        fp = fopen(outfile, "w");

        if (fp == NULL) {
            fprintf(stderr, "Failed to create output file.\n");
            exit(EXIT_FAILURE);
        }

        // open JSON array
        fprintf(fp, "[\n");

        // write initial coordinates to file
        write_coordinates(fp, n, points, end);
    }

    for (int t = 0; t < iterations; t++) {
        update_points(n, points, buffer, masses);

        // switch old and new
        Point *temp;
        temp = points;
        points = buffer;
        buffer = temp;

        // write updated coordinates to file
        if (STEPS && t % STEPS == 0) {
            write_coordinates(fp, n, points, end);
        }
    }

    if (STEPS) {
        // write final coordinates to file
        end = "";
        write_coordinates(fp, n, points, end);

        // close JSON array
        fprintf(fp, "]");

        // close file
        fclose(fp);
    }

    // cleanup
    free(masses);
    free(buffer);
    free(points);
}

int parse_int_arg(char *arg) {
    unsigned long n = 0;
    char *endptr;

    n = strtoul(arg, &endptr, 10);

    if (errno != 0) {
		perror("strtoul");
		exit(EXIT_FAILURE);
	}

    if (endptr == arg) {
        fprintf(stderr, "Failed to parse command line argument as number: %s\n", arg);
        exit(EXIT_FAILURE);
    }

    // clamp to int
    if (n > INT_MAX)
        return INT_MAX;
    else
        return n;
}

int main(int argc, char *argv[]) {
    int points;
    int iterations;

    srand(42);

    if (argc != 4) {
        fprintf(stderr, "Usage: %s POINTS ITERATIONS STEPS\n", argv[0]);
        fprintf(stderr, "    POINTS:     number of point masses\n");
        fprintf(stderr, "    ITERATIONS: number of simulation iterations\n");
        fprintf(stderr, "    STEPS:      number of steps between frames\n");
        fprintf(stderr, "                (set to 0 to disable data output)\n");
        fprintf(stderr, "Example: %s 100 10000 50\n", argv[0]);
        return EXIT_FAILURE;
    }

    points = parse_int_arg(argv[1]);
    iterations = parse_int_arg(argv[2]);
    STEPS = parse_int_arg(argv[3]);

    printf("Running N-Body simulation for: %d points, %d steps\n", points, iterations);
    if (STEPS) {
        printf("Writing point coordinates after every %d steps\n", STEPS);
    }

    simulation(iterations, points, "output.json");

    return EXIT_SUCCESS;
}
