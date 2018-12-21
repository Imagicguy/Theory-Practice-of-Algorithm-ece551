// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return 6 + (x + 2) * (y - 3);
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow > xHi || yLow > yHi || (xLow == xHi && yLow == yHi)) {
    return 0;
  }
  int count = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        count++;
      }
    }
  }
  return count;
}

int main() {
  for (int i = -6; i < 7; i++) {
    for (int j = -6; j < 7; j++) {
      printf("seq3(%d, %d) = %d\n", i, j, seq3(i, j));
    }
  }
  int data1[] = {7, 6, 3, 4};
  int data2[] = {0, 0, 5, 6};
  int data3[] = {4, 5, 3, 3};
  int data4[] = {1, 3, 2, 4};
  int * dataSet[] = {data1, data2, data3, data4};
  for (int i = 0; i < 4; i++) {
    printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
           dataSet[i][0],
           dataSet[i][1],
           dataSet[i][2],
           dataSet[i][3],
           countEvenInSeq3Range(dataSet[i][0], dataSet[i][1], dataSet[i][2], dataSet[i][3]));
  }
  return EXIT_SUCCESS;
}
