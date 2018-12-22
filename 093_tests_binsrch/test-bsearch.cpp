#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "function.h"

using namespace std;

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearch1(Function<int, int> * f, int low, int high);
int binarySearch(Function<int, int> * f, int low, int high) {
  int l = low;
  int h = high;
  int x, result;
  if (l == h) {
    result = f->invoke(l);
    if (result > 0)
      return h - 1;
    else
      return l;
  }

  while (true) {
    x = (l + h) / 2;

    result = f->invoke(x);
    if (result > 0)
      h = x;
    else if (result < 0)
      l = x;
    else
      return x;

    if (h - l <= 1)
      return l;

    if (x == high || x == low)
      return x;
  }
}

class Func1 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class Func2 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return -10 + arg / 100000; }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int max = 0;
  if (low == high) {
    max = 1;
  }
  else {
    max = log2(high - low) + 1;
  }
  Function<int, int> * func = new CountedIntFn(max, f, mesg);
  int ans = binarySearchForZero(func, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "fail to get right answers\n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int low = 0, high = 150000;
  Function<int, int> * sf = new Func1();
  check(sf, low, high, binarySearch(sf, low, high), "error in countedF");

  low = 52359;
  high = 52359;
  check(sf, low, high, binarySearch(sf, low, high), "error in countedF");

  low = 140000;
  high = 150000;
  check(sf, low, high, binarySearch(sf, low, high), "error in countedF");

  low = 1000;
  high = 1500;
  check(sf, low, high, binarySearch(sf, low, high), "error in countedF");

  low = 149990;
  high = 150000;
  check(sf, low, high, binarySearch(sf, low, high), "error in countedF");

  Function<int, int> * consf = new Func2();
  low = 1000;
  high = 1500000;
  check(consf, low, high, binarySearch(consf, low, high), "error in countedF");

  return 0;
}
