#pragma GCC optimize("Ofast")

#include <time.h>
#include "random.h"

unsigned int fast_random_seed = 948576312;

void reseed() {
    fast_random_seed = time(NULL);
}

unsigned int fast_random(const unsigned int bound) {
    fast_random_seed = (214013 * fast_random_seed + 2531011);
    return ((fast_random_seed >> 16) & 0x7FFF) % bound;
}
