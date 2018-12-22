#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "bstset.h"
using namespace std;

int main() {
  BstSet<int> * a = new BstSet<int>();
  BstSet<int> * b = new BstSet<int>();
  a->add(1);
  a->add(1);
  a->remove(1);
  cout << a->contains(1) << endl;
  a->add(2);
  b = a;
  cout << b->contains(2) << endl;
  //b->remove(2);
  //cout << b->contains(2) << endl;
  //BstSet<int> b;
  //b = *a;
  //b.remove(1);
  delete a;
  delete b;
  return 0;
}
