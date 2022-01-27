#pragma GCC optimize("Ofast")

#include <stdio.h>
#include "random.h"
#include "euler67.h"

void euler67() {
    printf("@ Euler 67\n");
    reseed();
    execute_euler67(45000, 1024);
}

int main() {
    euler67();
}
