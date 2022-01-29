// https://projecteuler.net/problem=83

#pragma GCC optimize("Ofast")

#include <malloc.h>
#include <stdio.h>
#include "euler83.h"
#include "random.h"
#include "timer.h"

static void free_matrix_v1(unsigned int **matrix, const unsigned int size) {
    unsigned int i;

    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

static void free_matrix_v2(unsigned int **matrix, const unsigned int size) {
    unsigned int i;

    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

static unsigned int **generate_matrix_v1(const unsigned int size, const unsigned int bound) {
    unsigned int **matrix = malloc(sizeof(unsigned int *) * size);
    unsigned int i;
    unsigned int y;

    for (i = 0; i < size; i++) {
        matrix[i] = (unsigned int *) malloc(sizeof(unsigned int) * (size));

        for (y = 0; y < size; y++) {
            matrix[i][y] = fast_random(bound);
        }
    }

    return matrix;
}

static unsigned int **generate_matrix_v2(const unsigned int size, const unsigned int bound) {
    unsigned int **matrix = malloc(sizeof(unsigned int *) * (size * 2 - 1));
    unsigned int index;
    unsigned int i;
    unsigned int y;

    for (i = 0; i < size; i++) {
        matrix[i] = (unsigned int *) malloc(sizeof(unsigned int) * (i + 1));

        for (y = 0; y <= i; y++) {
            matrix[i][y] = fast_random(bound);
        }
    }

    index = size;
    for (i = size - 2; i > 0; i--) {
        matrix[index] = (unsigned int *) malloc(sizeof(unsigned int) * (i + 1));

        for (y = 0; y <= i; y++) {
            matrix[index][y] = fast_random(bound);
        }

        index++;
    }

    matrix[index] = (unsigned int *) malloc(4);
    matrix[index][0] = fast_random(bound);
    return matrix;
}

static unsigned int find_minimum_path_v1(unsigned int **matrix, const unsigned int size) {
    unsigned int i;
    unsigned int y;
    unsigned int z;

    for (i = size - 1; i > 0; i--) {
        matrix[size - 1][i - 1] += matrix[size - 1][i];
        matrix[i - 1][size - 1] += matrix[i][size - 1];

        z = i;
        for (y = size - 2; y >= i;) {
            const unsigned int left = matrix[y + 1][z];
            const unsigned int right = matrix[y][z + 1];

            if (left <= right) {
                matrix[y][z] += left;
            } else {
                matrix[y][z] += right;
            }

            z++;
            y--;
        }
    }

    for (i = size - 1; i > 0; i--) {
        z = i;
        for (y = 0; y < i;) {
            const unsigned int left = matrix[z][y];
            const unsigned int right = matrix[z - 1][y + 1];

            if (left <= right) {
                matrix[z - 1][y] += left;
            } else {
                matrix[z - 1][y] += right;
            }

            z--;
            y++;
        }
    }

    return matrix[0][0];
}

static unsigned int find_minimum_path_v2(unsigned int **matrix, const unsigned int size) {
    unsigned int i;
    unsigned int y;
    unsigned int decremented_parent_diagonal_length = 1;

    for (i = size - 1; i > (size) / 2; i--) {
        const unsigned int *current_diagonal = matrix[i];
        unsigned int *parent_diagonal = matrix[i - 1];

        parent_diagonal[0] += current_diagonal[0];
        parent_diagonal[decremented_parent_diagonal_length] += current_diagonal[decremented_parent_diagonal_length - 1];

        for (y = 1; y < decremented_parent_diagonal_length; y++) {
            const unsigned int left = current_diagonal[y - 1];
            const unsigned int right = current_diagonal[y];

            if (left <= right) {
                parent_diagonal[y] += left;
            } else {
                parent_diagonal[y] += right;
            }
        }

        decremented_parent_diagonal_length++;
    }

    for (i = size / 2; i > 0; i--) {
        const unsigned int *current_diagonal = matrix[i];
        unsigned int *parent_diagonal = matrix[i - 1];

        for (y = 0; y < i; y++) {
            const unsigned int left = current_diagonal[y];
            const unsigned int right = current_diagonal[y + 1];

            if (left <= right) {
                parent_diagonal[y] += left;
            } else {
                parent_diagonal[y] += right;
            }
        }
    }

    return matrix[0][0];
}

static void test_v1() {
    unsigned int *matrix[] = {
            (unsigned int[]) {1, 9, 9, 1, 1, 1, 9, 9, 9},
            (unsigned int[]) {1, 9, 9, 1, 9, 1, 9, 9, 9},
            (unsigned int[]) {1, 1, 1, 1, 9, 1, 9, 1, 1},
            (unsigned int[]) {9, 9, 9, 9, 9, 1, 1, 9, 9},
            (unsigned int[]) {9, 1, 1, 1, 1, 1, 9, 1, 9},
            (unsigned int[]) {9, 1, 9, 9, 9, 9, 9, 9, 9},
            (unsigned int[]) {9, 1, 1, 1, 1, 1, 1, 1, 1},
            (unsigned int[]) {9, 9, 9, 9, 9, 9, 9, 9, 1},
            (unsigned int[]) {9, 9, 9, 9, 9, 9, 9, 9, 1}
    };


    const unsigned int result = find_minimum_path_v1(matrix, 9);
    if (result != 25) {
        fprintf(stderr, "%s", "test failed\n");
        exit(1);
    }
}

static void test_v2() {
    unsigned int *matrix[] = {
            (unsigned int[]) {1},
            (unsigned int[]) {1, 9},
            (unsigned int[]) {1, 9, 9},
            (unsigned int[]) {9, 1, 9, 1},
            (unsigned int[]) {9, 9, 1, 1, 1},
            (unsigned int[]) {9, 1, 9, 1, 9, 1},
            (unsigned int[]) {9, 1, 1, 9, 9, 1, 9},
            (unsigned int[]) {9, 1, 9, 1, 9, 1, 9, 9},
            (unsigned int[]) {9, 9, 1, 9, 1, 1, 9, 9, 9},
            (unsigned int[]) {9, 9, 1, 9, 1, 1, 1, 9},
            (unsigned int[]) {9, 9, 1, 9, 9, 1, 9},
            (unsigned int[]) {9, 9, 1, 9, 1, 9},
            (unsigned int[]) {9, 9, 1, 9, 9},
            (unsigned int[]) {9, 9, 1, 9},
            (unsigned int[]) {9, 9, 1},
            (unsigned int[]) {9, 1},
            (unsigned int[]) {1}
    };

    const unsigned int result = find_minimum_path_v2(matrix, 17);
    if (result != 25) {
        fprintf(stderr, "%s", "test failed\n");
        exit(1);
    }
}


static void execute_v1(const unsigned int size, const unsigned int bound) {
    double execution_time;
    printf("Generating a matrix with the following parameters: [size: %d, bound: [0:%d), total elements: %d]\n",
           size, bound, size * size
    );
    unsigned int **matrix = generate_matrix_v1(size, bound);

    printf("Starting (V1)...\n");
    timer_start();
    const unsigned int result = find_minimum_path_v1(matrix, size);
    execution_time = timer_stop();

    printf("Result: %d, execution time: %f\n\n\n", result, execution_time);
    test_v1();
    free_matrix_v1(matrix, size);
}

static void execute_v2(const unsigned int size, const unsigned int bound) {
    const unsigned int matrix_updated_size = size * 2 - 1;
    double execution_time;
    printf("Generating a matrix with the following parameters: [size: %d, bound: [0:%d), total elements: %d]\n",
           size, bound, size * size
    );
    unsigned int **matrix = generate_matrix_v2(size, bound);

    printf("Starting (V2)...\n");
    timer_start();
    const unsigned int result = find_minimum_path_v2(matrix, matrix_updated_size);
    execution_time = timer_stop();

    printf("Result: %d, execution time: %f\n\n\n", result, execution_time);
    test_v2();
    free_matrix_v2(matrix, matrix_updated_size);
}

void execute_euler83(const unsigned int size, const unsigned int bound) {
    execute_v1(size, bound);
    printf("\n\n");
    execute_v2(size, bound);
}

