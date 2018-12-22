#include "readFreq.h"

#include <stdio.h>
#include <stdlib.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * array = new uint64_t[257];
  ifstream file(fname);
  if (file.is_open()) {
    for (int i = 0; i < 256; i++) {
      array[i] = 0;
    }
    array[256] = 1;
    char c;
    while (file.get(c)) {
      unsigned char cc = c;
      array[int(cc)]++;
    }
  }
  else {
    cout << "can't open the file\n";
    exit(EXIT_FAILURE);
  }
  file.close();

  return array;
}
