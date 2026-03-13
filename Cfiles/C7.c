#include "array.h"
#include <stdio.h>

int shiftL(int ind) { // starts from index and puts each item from right to current
    int count = 0;
    for (int i = ind; i < ArraySize-1; i++) {
        put(i, get(i+1));
        count += 2;
    }
    return count;
}

int shiftR(int ind) { // starts from end and puts each box from left to current
    int count = 0;
    for (int i = ArraySize-1; i > ind; i--) {
        put(i, get(i-1));
        count += 2;
    }
    return count; 
}

int main() {
    int count = 0;
    int index[3] = {0, 0, 0};
    char command;
    while (scanf(" %c", &command) == 1) {
        int stack;
        int num;
        if (command == 'u') {
            scanf("%d",  &stack);
            scanf("%d",  &num);
            count += shiftR(index[stack]);
            put(index[stack], num);
            count++;

            if (stack == 0) {
                index[0]++;
                index[1]++;  
                index[2]++;
            } else if (stack == 1) {
                index[1]++;
                index[2]++;
            } else if (stack == 2) {
                index[2]++;
            } else {
                return -3;
            }


        } else if (command == 'o') {
            scanf("%d",  &stack);
            printf("%d\n", get(index[stack]-1));
            count++;
            count += shiftL(index[stack]-1);

            if (stack == 0) {
                index[0]--;
                index[1]--;  
                index[2]--;
            } else if (stack == 1) {
                index[1]--;
                index[2]--;
            } else if (stack == 2) {
                index[2]--;
            } else {
                return -4;
            } 
        } else {
            return -10;
        }
    }

    
}

