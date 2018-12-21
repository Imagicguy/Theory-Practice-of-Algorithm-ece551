#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  return x * x + 3 * x + 1;
}

int sumSeq2(int low, int high) {
  int result = 0;
  if (low >= high) {
    return 0;
  }
  for (int i = low; i < high; i++) {
    result += seq2(i);
  }
  return result;
}

int main() {
  for (int i = -8; i < 19; i++) {
    printf("seq2(%d) = %d\n", i, seq2(i));
  }
  int low_ind[] = {-6, -3, 5, 7, -3, -4};
  int high_ind[] = {2, 8, 5, 6, -2, 13};
  for (int j = 0; j < 6; j++) {
    printf("sumSeq2(%d,%d) = %d\n", low_ind[j], high_ind[j], sumSeq2(low_ind[j], high_ind[j]));
  }
  return EXIT_SUCCESS;
}
