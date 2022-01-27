#pragma GCC optimize("Ofast")

#include <malloc.h>
#include <time.h>
#include <stdio.h>
#include "euler67.h"
#include "random.h"

unsigned int **generate_pyramid(const int depth, const int bound) {
    unsigned int **pyramid = malloc(sizeof(int *) * depth);
    for (int i = 0; i < depth; i++) {
        pyramid[i] = (unsigned int *) malloc(sizeof(int) * (i + 1));

        for (int y = 0; y <= i; y++) {
            pyramid[i][y] = fast_random(bound);
        }
    }

    return pyramid;
}

unsigned int find_maximum_sum_of_path(unsigned int **pyramid, const int depth) {
    for (int i = depth - 1; i > 0; i--) {
        const unsigned int *stage = pyramid[i];
        unsigned int *parent_stage = pyramid[i - 1];

        for (int y = 0; y < i; y++) {
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


void execute_euler67(const int depth, const int bound) {
    printf("Generating a pyramid with the following parameters: [depth: %d, bound: %d, total elements: %d]\n",
           depth, bound, (depth / 2) * (depth + 1)
    );
    unsigned int **pyramid = generate_pyramid(depth, bound);

    const clock_t begin_time = clock();
    const unsigned int sum = find_maximum_sum_of_path(pyramid, depth);
    const clock_t end_time = clock();

    const double execution_time = (double) (end_time - begin_time) / CLOCKS_PER_SEC;
    printf("Result: %d, execution time: %f\n", sum, execution_time);
}
