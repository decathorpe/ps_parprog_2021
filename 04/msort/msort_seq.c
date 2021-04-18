#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// get wall time in seconds
double walltime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    double secs = (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
    return secs;
}

// prints (int32_t *) arrays in nice formats
// - length 10: [-2, -1, -1, 0, 0, 0, 1, 1, 2, 2]
// - length 1:  [42]
// - length 0:  []
// - null pointers: NULL
void print_int32_tp_array(int32_t **array, size_t length, char *name) {
    if (length == 0) {
        printf("%s: []\n", name);
        return;
    }

    printf("%s: [", name);
    for (size_t i = 0; i < length-1; i++) {
        if (array[i] == NULL) {
            printf("NULL");
        } else {
            printf("%d, ", *array[i]);
        }
    }

    if (array[length-1] == NULL) {
        printf("NULL");
    } else {
        printf("%d", *array[length-1]);
    }

    printf("]\n");
}

int is_sorted_int32_tp_array(int32_t **array, size_t length) {
    int32_t max = *array[0];

    for (size_t i = 1; i < length; i++) {
        if (*array[i] < max) {
            return 0;
        } else {
            max = *array[i];
        }
    }

    return 1;
}

// merge algorithm for to sorted sub-arrays
void merge(int32_t **array, size_t length, int32_t **temp) {
    size_t left_length = length / 2;

    // current indices in left array, right array, and sorted array
    size_t left = 0;
    size_t right = left_length;
    size_t sorted = 0;

    // iterate until either the left or the right array is "empty"
    while (left < left_length && right < length) {
        if (*array[left] <= *array[right]) {
            // left element is smaller
            temp[sorted] = array[left];
            left++;
            sorted++;
        } else {
            // right element is smaller
            temp[sorted] = array[right];
            right++;
            sorted++;
        }
    }

    // take remaining sorted elements from left array, if any
    while (left < left_length) {
        temp[sorted] = array[left];
        left++;
        sorted++;
    }

    // take remaining sorted elements from right array, if any
    while (right < length) {
        temp[sorted] = array[right];
        right++;
        sorted++;
    }

    // overwrite input array with values from temporary array
    for (size_t i = 0; i < length; i++) {
        array[i] = temp[i];
    }
}

// recursive merge-sort implementation
void msort_rec(int32_t **array, size_t length, int32_t **temp) {
    // if length of array is zero or one, then it's already sorted
    if (length < 2) {
        return;
    }

    // small optimization for arrays of size 2
    if (length == 2) {
        // swap elements if the second one is smaller
        if (*array[1] < *array[0]) {
            int32_t *tmp = array[1];
            array[0] = array[1];
            array[1] = tmp;
        }

        return;
    }

    // split input array into left and right half
    // if length is odd, the left half is always smaller by 1
    size_t left_length = length / 2;
    size_t right_length = length - left_length;

    // sort left and right halves separately
    msort_rec(array, left_length, temp);
    msort_rec(array+left_length, right_length, temp + left_length);

    // merge sorted sub-arrays
    merge(array, length, temp);
}

void msort(int32_t **array, size_t length) {
    // allocate temporary memory once
    // shared by merge steps in all recursive calls
    int32_t **temp = malloc(length * sizeof(int32_t *));

    msort_rec(array, length, temp);

    free(temp);
}

// test unique elements
// sort   [5, 4, 3, 2, 1, 0, -1, -2, -3, -4]
// expect [-4, -3, -2, -1, 0, 1, 2, 3, 4, 5]
void test1(void) {
    int32_t *a1 = malloc(10 * sizeof(int32_t));
    for (int i = 0; i < 10; i++) {
        a1[i] = 5 - i;
    }
    int32_t **p1 = malloc(10 * sizeof(int32_t *));
    for (int i = 0; i < 10; i++) {
        p1[i] = &a1[i];
    }

    print_int32_tp_array(p1, 10, "sort unique  ");
    msort(p1, 10);
    print_int32_tp_array(p1, 10, "sorted unique");

    free(p1);
    free(a1);
}

// test length one
// sort   [42]
// expect [42]
void test2(void) {
    int32_t *a2 = malloc(1 * sizeof(int32_t));
    for (int i = 0; i < 1; i++) {
        a2[i] = 42;
    }
    int32_t **p2 = malloc(1 * sizeof(int32_t *));
    for (int i = 0; i < 1; i++) {
        p2[i] = &a2[i];
    }

    print_int32_tp_array(p2, 1, "sort one  ");
    msort(p2, 1);
    print_int32_tp_array(p2, 1, "sorted one");

    free(p2);
    free(a2);
}

// test length zero
// sort   []
// expect []
void test3(void) {
    int32_t *a3 = malloc(0 * sizeof(int32_t));
    int32_t **p3 = malloc(0 * sizeof(int32_t *));

    print_int32_tp_array(p3, 0, "sort empty  ");
    msort(p3, 0);
    print_int32_tp_array(p3, 0, "sorted empty");

    free(p3);
    free(a3);
}

// test non-unique elements
// sort   [2, 2, 1, 1, 0, 0, 0, -1, -1, -2]
// expect [-2, -1, -1, 0, 0, 0, 1, 1, 2, 2]
void test4(void) {
    int32_t *a4 = malloc(10 * sizeof(int32_t));
    for (int i = 0; i < 10; i++) {
        a4[i] = (5-i) / 2;
    }
    int32_t **p4 = malloc(10 * sizeof(int32_t *));
    for (int i = 0; i < 10; i++) {
        p4[i] = &a4[i];
    }

    print_int32_tp_array(p4, 10, "sort non-unique  ");
    msort(p4, 10);
    print_int32_tp_array(p4, 10, "sorted non-unique");

    free(p4);
    free(a4);
}

/*
int main(void) {
    test1();
    test2();
    test3();
    test4();

    return EXIT_SUCCESS;
}
*/

const size_t ARRAY_SIZE = 100000000;

int main(void) {
    srand(7);

    int32_t *array = malloc(ARRAY_SIZE * sizeof(int32_t));
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() - (RAND_MAX / 2);
    }

    int32_t **aptr = malloc(ARRAY_SIZE * sizeof(int32_t *));
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        aptr[i] = &array[i];
    }

    // -----------------------------------------------------------------------

    double start_time = walltime();

    msort(aptr, ARRAY_SIZE);

    double end_time = walltime();

    // -----------------------------------------------------------------------

    printf("time: %2.5f seconds\n", end_time - start_time);

    int status = EXIT_SUCCESS;
    if (!is_sorted_int32_tp_array(aptr, ARRAY_SIZE)) {
        printf("Array is not sorted!\n");
        status = EXIT_FAILURE;
    }

    free(aptr);
    free(array);

    return status;
}
