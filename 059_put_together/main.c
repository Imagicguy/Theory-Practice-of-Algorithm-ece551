#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "failed to open list file\n");
    exit(EXIT_FAILURE);
  }
  counts_t * c = createCounts();
  char * len = NULL;
  size_t sz;
  ssize_t a = 0;
  while ((a = getline(&len, &sz, f)) > 0) {
    len[a - 1] = '\0';
    char * value = lookupValue(kvPairs, len);
    addCount(c, value);
  }
  free(len);
  if (fclose(f) != 0) {
    fprintf(stderr, "failed to close list file\n");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    fprintf(stderr, "Usage: inappropriate input\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //printKVs(kv);
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE * f = fopen(outName, "w");
    printCounts(c, f);
    if (fclose(f) != 0) {
      free(outName);
      freeCounts(c);
      fprintf(stderr, "outName failed to close\n");
      exit(EXIT_FAILURE);
    }
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);

  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)

  //count from 2 to argc (call the number you count i)

  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
