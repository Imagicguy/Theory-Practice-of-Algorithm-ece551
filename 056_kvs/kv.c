#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//sharenzhuxin
kvpair_t * pair_maker(char * line_ptr) {
  kvpair_t * cur = malloc(sizeof(*cur));
  cur->key = NULL;
  cur->value = NULL;
  size_t label = 0;
  while (*(line_ptr + label) != '=') {
    label++;
  }
  char * key_cur = NULL;
  char * value_cur = NULL;
  key_cur = malloc((label + 2) * sizeof(*key_cur));
  value_cur = malloc(((strlen(line_ptr) - label - 1) * sizeof(*key_cur)));

  for (size_t i = 0; i < label; i++) {
    key_cur[i] = *(line_ptr + i);
  }
  key_cur[label] = '\0';
  label++;
  size_t value_init = label;
  while (*(line_ptr + label) != '\n') {
    //printf("%c", *(line_ptr + label));
    value_cur[label - value_init] = *(line_ptr + label);
    label++;
    //printf("%c", cur->value[label]);
  }
  value_cur[label - value_init] = '\0';
  cur->key = key_cur;
  cur->value = value_cur;
  key_cur = NULL;
  value_cur = NULL;
  return cur;
}

kvarray_t * readKVs(const char * fname) {
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->length = 0;
  kvarray->array_pointer = NULL;
  FILE * f = fopen(fname, "r");
  char * line = NULL;
  size_t sz;
  kvpair_t * cur = NULL;
  kvpair_t ** array_ptr = NULL;
  if (f == NULL) {
    printf("Could not open pairfile");
    exit(EXIT_FAILURE);
  }
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    cur = pair_maker(line);
    array_ptr = realloc(array_ptr, (i + 1) * sizeof(*cur));
    array_ptr[i] = cur;
    cur = NULL;
    i++;
  }
  free(line);
  kvarray->array_pointer = array_ptr;
  kvarray->length = i;
  if (fclose(f) != 0) {
    perror("Failed to close the pair file");
    exit(EXIT_FAILURE);
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->array_pointer[i]->value);
    free(pairs->array_pointer[i]->key);
    free(pairs->array_pointer[i]);
  }
  free(pairs->array_pointer);
  pairs->array_pointer = NULL;
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  size_t lengths = pairs->length;
  for (size_t i = 0; i < lengths; i++) {
    printf(
        "key = '%s' value = '%s'\n", pairs->array_pointer[i]->key, pairs->array_pointer[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->array_pointer[i]->key, key) == 0) {
      //printf("%s\n", pairs->array_pointer[i]->value);
      return pairs->array_pointer[i]->value;
    }
  }
  return NULL;
}
