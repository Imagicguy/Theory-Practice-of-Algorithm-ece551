#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void decrypt(FILE * f) {
  int c;
  int countArray[26] = {0};
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      for (int i = 0; i < 26; i++) {
        int temp = alphabet[i];
        if (temp == c) {
          countArray[i]++;
        }
      }
    }
  }
  int max = 0;
  int maxIndex = 0;
  for (int j = 0; j < 26; j++) {
    if (countArray[j] > max) {
      max = countArray[j];
      maxIndex = j;
    }
  }
  //for (int k = 0; k < 26; k++) {
  //printf("%d", countArray[k]);
  //}
  // printf("\n");
  //printf("%d\n", maxIndex);
  maxIndex += 'a' - 'e';
  //printf("%d\n", maxIndex);
  if (maxIndex < 0) {
    maxIndex += 26;
  }
  printf("%d\n", maxIndex);
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
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
