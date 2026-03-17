#include "C10.h"
#include <stdio.h>

int mem[100];
/* 
current value
current value copy
reverse palin accum, 
*/

void printNums(int m, int n) {
    mem[0] = m;
    goto N;
    
    N: 
    mem[1] = mem[0];
    goto R;
    
    R: 
    mem[2] = mem[2]*10 + mem[1]%10; // 123, 654 -> 6543
    mem[1] = (mem[1]-mem[1]%10)/10; // 123 -> 12
    if (mem[1] == 0) {
        goto R1;
    }
    goto R;

    R1:
    if (mem[2] == mem[1]) {
        goto P;
    }
    goto Add;


    



    P: 
    printf("%d\n", mem[0]);
    goto Add;


    Add:
    if (mem[0] == n+1) {
        return;
    }
    mem[0]++;
    goto N;
}

int main() {

  int m, n;

  while (scanf("%d %d", &m, &n) == 2) {

    printNums(m, n);

  }

}