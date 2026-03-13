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
    int remainder = num % pow;
    //printf("%d\n", pow);
    //printf("%d\n", num);
    int digitpart = num - num%pow;
    int digit = digitpart/pow;
    if (num == 0) {
        printf("0");
    } else if(1 <= digit && digit <= 9) {
        printf("%d", digit);
    } else if (10 <= digit && digit <= 15) {
        char hex = 'a'+digit-10;
        //printf("   %d    ", digit);
        printf("%c", hex);
    } else {
        
    }
    
    if (pow != 1) {
        printdectohex(remainder, pow/16);
    }
}

int main() {
    int sum = sumInt(0);
    if (sum == 0) {
        printf("0");
    } else {
    printdectohex(sum, 16*16*16*16*16*16*16);
    }
    printf("\n");
    return 0;
}