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
    else if (c >= '0' && c <= '9') return getIntHelper(acc * 16 + c - '0');
    else if (c >= 'a' && c <= 'f') return getIntHelper(acc * 16 + c - 'a' + 10);
    else if (c >= 'A' && c <= 'F') return getIntHelper(acc * 16 + c - 'A' + 10);   
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

void printdectohex(int num, int pow) {
    int remainder = num % (pow*16);
    int digit;
}

int main() {
    //printdectohex(sumInt(0), 1);
    printf("%d", 16*16*16*16*16*16*16);
    printf("\n");
    return 0;
}