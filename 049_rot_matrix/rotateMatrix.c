#include <stdio.h>
#include <stdlib.h>
int rotate(FILE * f) {
  int c;
  int storage[10][10] = {0};
  for (int i = 9; i >= 0; i--) {
    for (int j = 0; j < 10; j++) {
      if ((c = fgetc(f)) == EOF) {
        fprintf(stderr, "error!not enough input\n");
        return -1;
      }
      else {
        if (c > 127 || c < 0) {
          fprintf(stderr, "error!no-typeable!");
          return -1;
        }
        if (c != 10) {
          storage[j][i] = c;
        }
        else {
          fprintf(stderr, "error!wrong length\n");
          return -1;
        }
      }
    }
    if ((c = fgetc(f)) == EOF) {
      fprintf(stderr, "error!not enough input\n");
      return -1;
    }
    else {
      if (c != 10) {
        fprintf(stderr, "error!not wrong length\n");
        return -1;
      }
    }
  }
  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "error!not enough input\n");
    return -1;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", storage[i][j]);
    }
    printf("\n");
  }
  return 0;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: decrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = rotate(f);
  if (key == -1) {
    return EXIT_FAILURE;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file");
    return EXIT_FAILURE;
  }
}
