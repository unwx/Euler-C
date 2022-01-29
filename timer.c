#pragma GCC optimize("Ofast")

#include "timer.h"
#include <sys/time.h>

static struct timeval timeval_start;
static struct timeval timeval_end;

void timer_start() {
    gettimeofday(&timeval_start, NULL);
}

double timer_stop() {
    gettimeofday(&timeval_end, NULL);
    return (double) (timeval_end.tv_usec - timeval_start.tv_usec) / 1000000 + (double) (timeval_end.tv_sec - timeval_start.tv_sec);
}