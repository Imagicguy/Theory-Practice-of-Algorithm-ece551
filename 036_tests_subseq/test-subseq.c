#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

int main() {
  int array1[] = {};
  int array2[] = {3, 2, 1};
  int array3[] = {1, 2, 3, 2, 4, 5};
  int array4[] = {1, 1, 1};
  int array5[] = {-3, -2, -1, -1, -1};
  int array6[] = {92768, 92769, 92770};
  int array7[] = {1, 2, 3, 1, 2, 3, 4};
  int array8[] = {1, 2, 3, 4, 1, 2, 3};
  int array9[] = {2, 4, 2, 4, 2, 4, 2, 4};
  int array10[] = {1, 2, 3, 3, 3, 2};
  int array11[] = {1, 2, 3, 3, 3, 4};
  int * array12 = NULL;
  int array13[] = {0};
  int array14[] = {0, -1, -2, 1, 2};
  int * add_arr[] = {array1,
                     array2,
                     array3,
                     array4,
                     array5,
                     array6,
                     array7,
                     array8,
                     array9,
                     array10,
                     array11,
                     array12,
                     array13,
                     array14};
  size_t ans[] = {0, 1, 3, 1, 3, 3, 4, 4, 2, 3, 3, 0, 1, 3};
  int size[] = {0, 3, 6, 3, 5, 3, 7, 7, 8, 6, 6, 0, 1, 5};
  for (int i = 0; i < 14; i++) {
    if (ans[i] != maxSeq(add_arr[i], size[i])) {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
