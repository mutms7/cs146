#include "C10.h"
#include <stdio.h>

int mem[100];


void printNums(int m, int n) {
    if (m > n) 
        goto C;
    

    A:
    mem[0] = m;
    goto N;

    C:
    mem[0] = n;
    n = m;
    m = mem[0];
    goto A;
    
    N: 
    mem[1] = mem[0];
    goto R;
    
    R: 
    mem[2] = mem[2]*10 + mem[1]%10; 
    mem[1] = (mem[1]-mem[1]%10)/10; 
    if (mem[1] == 0) 
        goto R1;
    

    goto R;

    R1:
    if (mem[2] == mem[0]) 
        goto Sm;
    
    goto Add;

    Sm:
    mem[2] = 2;
    goto S;

    S:
    if (mem[0]%(mem[2]*mem[2]) == 0) 
        goto Add;
    
    goto S1;

    S1:
    if (mem[2]*mem[2] > mem[0]) 
        goto P;
    
    mem[2]++;
    goto S;


    P: 
    printf("%d\n", mem[0]);
    goto Add;


    Add:
    if (mem[0] >= n) 
        return;
    
    mem[0]++;
    mem[2] = 0;
    goto N;
}
