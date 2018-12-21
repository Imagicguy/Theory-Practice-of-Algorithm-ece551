#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

int run_check(unsigned x, unsigned y, unsigned expected_ans, int isSucceed) {
  unsigned test_ans = power(x, y);
  if (test_ans != expected_ans) {
    printf("haha\n");
    if (isSucceed == 1) {
      isSucceed = 0;
    }
  }
  return isSucceed;
}
int main() {
  unsigned input_x[] = {0, 1, 3, 1, 1, 3, 1, 0, 3, 1, 3, -3, 65537};
  unsigned input_y[] = {0, -2, 0, 1, 4, 1, 0, 3, 3, -1, 2, 2, 1};
  unsigned exp_ans[] = {1, 1, 1, 1, 1, 3, 1, 0, 27, 1, 9, 9, 65537};
  int isSucceed = 1;
  for (int i = 0; i < 13; i++) {
    isSucceed = run_check(input_x[i], input_y[i], exp_ans[i], isSucceed);
  }

  if (isSucceed == 0) {
    exit(EXIT_FAILURE);
  }
  else {
    exit(EXIT_SUCCESS);
  }
}
