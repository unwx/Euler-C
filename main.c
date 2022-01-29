#pragma GCC optimize("Ofast")

#include <stdio.h>
#include "random.h"
#include "euler67.h"
#include "euler83.h"

static void next() {
    printf("\n\n\n");
}

static void euler83() {
    printf("@(https://projecteuler.net/problem=83) Euler 83\n");
    reseed();
    execute_euler83(37500, 1024);
}

static void euler67() {
    printf("@(https://projecteuler.net/problem=67) Euler 67\n");
    reseed();
    execute_euler67(45000, 1024);
}

int main() {
    euler67();
    next();
    euler83();
    getchar();
}
