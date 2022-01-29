// https://projecteuler.net/problem=67

#pragma GCC optimize("Ofast")

#include <malloc.h>
#include <stdio.h>
#include "euler67.h"
#include "random.h"
#include "timer.h"

static void free_pyramid(unsigned int **pyramid, const unsigned int depth) {
    unsigned int i;
    for (i = 0; i < depth; i++) {
        free(pyramid[i]);
    }

    free(pyramid);
}

static unsigned int **generate_pyramid(const unsigned int depth, const unsigned int bound) {
    unsigned int **pyramid = malloc(sizeof(unsigned int *) * depth);
    unsigned int i;
    unsigned int y;

    for (i = 0; i < depth; i++) {
        pyramid[i] = (unsigned int *) malloc(sizeof(unsigned int) * (i + 1));

        for (y = 0; y <= i; y++) {
            pyramid[i][y] = fast_random(bound);
        }
    }

    return pyramid;
}

static unsigned int find_maximum_sum_of_path(unsigned int **pyramid, const unsigned int depth) {
    unsigned int i;
    unsigned int y;

    for (i = depth - 1; i > 0; i--) {
        const unsigned int *stage = pyramid[i];
        unsigned int *parent_stage = pyramid[i - 1];

        for (y = 0; y < i; y++) {
            const unsigned int left = stage[y];
            const unsigned int right = stage[y + 1];

            if (left >= right) {
                parent_stage[y] += left;
            } else {
                parent_stage[y] += right;
            }
        }
    }

    return pyramid[0][0];
}


void execute_euler67(const unsigned int depth, const unsigned int bound) {
    double execution_time;

    printf("Generating a pyramid with the following parameters: [depth: %d, bound: [0:%d), total elements: %d]\n",
           depth, bound, (depth / 2) * (depth + 1)
    );
    unsigned int **pyramid = generate_pyramid(depth, bound);

    printf("Starting...\n");
    timer_start();
    const unsigned int result = find_maximum_sum_of_path(pyramid, depth);
    execution_time = timer_stop();

    printf("Result: %d, execution time: %f\n", result, execution_time);
    free_pyramid(pyramid, depth);
}
