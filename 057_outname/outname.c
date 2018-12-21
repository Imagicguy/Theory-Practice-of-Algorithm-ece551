#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  if (inputName == NULL) {
    printf("No file detected !\n");
    exit(EXIT_FAILURE);
  }
  size_t length = strlen(inputName);
  char * input_name_memo = malloc(length * sizeof(*inputName) + 8);
  strcpy(input_name_memo, inputName);
  strcat(input_name_memo, ".counts");
  return input_name_memo;
}
