#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //  for (int i = 0; i < 257; i++) {
  //std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
  //if (it != theMap.end()) {
  //  bfw.writeBitString(it->second);
  //}
  //}

  std::ifstream s(inFile);
  char c;
  while (s.get(c)) {
    unsigned char cc = c;
    bfw.writeBitString(theMap.find(unsigned(cc))->second);
  }
  bfw.writeBitString(theMap.find(256)->second);
  //  for (std::map<unsigned, BitString>::const_iterator it = theMap.begin(); it != theMap.end();
  //   ++it) {
  //if (it->first != EOF) {
  //  bfw.writeBitString(it->second);
  //}
  //else {
  //  continue;
  //}
}
//bfw.writeBitString();
//WRITE YOUR CODE HERE!
//open the input file for reading

//You need to read the input file, lookup the characters in the map,
//and write the proper bit string with the BitFileWriter

//dont forget to lookup 256 for the EOF marker, and write it out.

//BitFileWriter will close the output file in its destructor
//but you probably need to close your input file.

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  std::map<unsigned, BitString> theMap;
  uint64_t * array = readFrequencies(argv[1]);
  Node * tree = buildTree(array);
  delete[] array;
  BitString b;
  tree->buildMap(b, theMap);
  delete tree;
  writeCompressedOutput(argv[1], argv[2], theMap);
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  return EXIT_SUCCESS;
}
