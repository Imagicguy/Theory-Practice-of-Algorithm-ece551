#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int l = low;
  int h = high;
  int x, result;
  if (l == h) {
    result = f->invoke(l);
    if (result < 0)
      return h - 1;
    else
      return l;
  }

  while (true) {
    x = (l + h) / 2;

    result = f->invoke(x);
    if (result > 0)
      h = x;
    else if (result < 0)
      l = x;
    else
      return x;

    if (h - l <= 1)
      return l;

    if (x == high || x == low)
      return x;
  }
}
