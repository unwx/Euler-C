#pragma GCC optimize("Ofast")

#include <malloc.h>
#include "array_utils.h"

void free_array_2d(unsigned int **array, const unsigned int depth) {
    unsigned int i;
    for (i = 0; i < depth; i++) {
        free(array[i]);
    }

    free(array);
}