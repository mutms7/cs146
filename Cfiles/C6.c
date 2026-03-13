#include "C6.h"
#include <stdio.h>
#include <ctype.h>


int isqrt(int n);
int isqrtHelp(int i, int n);

int isqrtHelp(int i, int n) {
    if (i > n / i) {
        return (i-1);
    } else {
        return isqrtHelp(i + 1, n);
    }
}

int isqrt(int n) {
    if (n == 0) return 0;
    return isqrtHelp(1, n);
}

int prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= isqrt(n); ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int cont(int n, int factor) {
    if (n % factor == 0) {
        return 1;
    }
    return 0;
}

void prime_factors(int n) {
    for (int i = 2; i <= n; ++i) {
        if (prime(i)) {
            while (cont(n, i)) {
                printf("%d\n", i);
                n = n / i;
            }
        }
    }
}
