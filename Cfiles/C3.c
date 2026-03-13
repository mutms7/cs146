#include <stdio.h>

#include "C3.h"

int isqrt(int n) {
  int num = 0;
  while (num*num <= n && num*num >= 0) {
++num;
}
return num-1;
}
