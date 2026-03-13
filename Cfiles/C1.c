#include <stdio.h>

int skipws() {
    char c = getchar();
    if (EOF == c) {
        ungetc(c, stdin);
        return EOF;
    } else if (c == ' ' || c == '\t' || c == '\n') {
        return skipws();
    } else {
        ungetc(c, stdin);
        return 0;
    }
}

int getIntHelper(int acc) {
    char c = getchar();
    if (EOF == c || c == ' ' || c == '\t' || c == '\n') {
        return acc;
    }
    else if (c >= '0' && c <= '9') return getIntHelper(acc * 10 + c - '0');
    else return -10;
}

int getInt() {
    if (skipws() == EOF) {
        return -1;
    }
    return getIntHelper(0);
}

int sumInt(int acc) {
    int c = getInt();
    if (c == -1) {
        return acc;
    } else {
        return sumInt(acc + c);
    }
}

int main() {
    int num = sumInt(0);
    printf("%d\n", num);
    return 0;
}
