#include "C4.h"
#include <stdio.h>

int isqrt(int n) {
   int num = 0;
   while (num*num <= n && num*num >= 0) {
 ++num;
 }
 return num-1;
 }

int issqr(int n) {
int s = 0;
while (s*s <= n) {
  if (s*s == n) {
return s;
}
++s;
}
return -1;
}

void sumsqr(int n) {
  	for (int i = isqrt(n/2); i <= isqrt(n); i++) {
		if (issqr(n-i*i) != -1) {
			printf("%d %d\n", i, issqr(n-i*i));
		}
	} 
}

