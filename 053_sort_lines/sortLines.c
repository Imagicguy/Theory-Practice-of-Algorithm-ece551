#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void helper(FILE * file_name) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, file_name) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}
int main(int argc, char ** argv) {
  if (argv == NULL) {
    exit(EXIT_FAILURE);
  }
  if (argc == 1) {
    helper(stdin);
  }
  else {
    int num_file = argc - 1;
    for (int i = 1; i <= num_file; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "failed to open file %d", i);
        exit(EXIT_FAILURE);
      }
      helper(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "failed to close file %d", i);
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
