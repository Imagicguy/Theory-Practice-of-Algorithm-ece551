// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return -3 + 4 * x;
}

void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
    return;
  }
  for (int i = low; i < high; i++) {
    printf("%d", seq1(i));
    if (i != high - 1) {
      printf(", ");
    }
  }
  printf("\n");
  return;
}

int main() {
  for (int i = -8; i < 15; i++) {
    printf("seq1(%d) = %d\n", i, seq1(i));
  }
  int low_ind[] = {-6, -3, 5, 7, -3};
  int high_ind[] = {2, 8, 5, 6, -2};
  for (int j = 0; j < 5; j++) {
    printf("printSeq1Range(%d,%d)\n", low_ind[j], high_ind[j]);
    printSeq1Range(low_ind[j], high_ind[j]);
  }
  return EXIT_SUCCESS;
}
