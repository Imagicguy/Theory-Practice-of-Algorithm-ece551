#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  if (array == NULL || n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  size_t count = 1;
  size_t maxCount = 0;
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      count++;
    }
    else {
      if (count > maxCount) {
        maxCount = count;
      }
      count = 1;
    }
    if (count > maxCount) {
      maxCount = count;
    }
  }
  return maxCount;
}
