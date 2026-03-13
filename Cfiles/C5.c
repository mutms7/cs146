#include "C5.h"
#include <stdio.h>
#include <ctype.h>

int check(int n);

void regular(int n) {
    for (int i = 1; i <= n; ++i) {
        if (check(i)) {
            printf("%d\n", i);
        }
    }

}

int check(int n) {
    if (n <= 6) {
        return 1;
    }
    if (n % 2 == 0) {
        return (check (n / 2));
    } else if (n % 3 == 0) {
        return (check (n / 3));
    } else if (n % 5 == 0) {
        return (check (n / 5));
    }
    return 0;
}
