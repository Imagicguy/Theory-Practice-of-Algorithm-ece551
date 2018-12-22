
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdlib>

#include "il.h"
void testList(void) {
  IntList a;
  assert(a.head == NULL && a.tail == NULL && a.getSize() == 0);  //test default constructor
  IntList b = IntList(a);
  assert(b.getSize() == 0 && b.head == NULL && b.tail == NULL);
  a.addFront(1);  // a = 1
  assert(a.getSize() == 1 && a.head->data == 1 && a.tail->data == 1 && a.tail->prev == NULL &&
         a.head->next == NULL);
  a.addFront(2);  // a = 2, 1
  assert(a.getSize() == 2 && a.head->next->data == 1 && a.tail->data == 1 &&
         a.tail->prev->data == 2 && a.head->data == 2);
  IntList c;
  c = a;
  assert(c.getSize() == 2 && c.head != NULL && c.head != NULL);
  a.addBack(2);  //a = 2,1,2
  assert(a.getSize() == 3 && a.tail->data == 2 && a.tail->prev->data == 1 &&
         a.head->next->data == 1 && a.head->data == 2);
  a.remove(2);  // a = 1,2
  assert(a.getSize() == 2 && a.head->data == 1 && a.tail->data == 2 && a.tail->prev->data == 1 &&
         a.head->next->data == 2);
  assert(a.find(1) == 0 && a.find(3) == -1 && a.find(-2) == -1);
  assert(a.remove(6) == false);
  assert(a[0] == 1);
  a.addFront(3);  //3,1,2
  a.addFront(4);  //4,3,1,2
  a.remove(1);    //4,3,2
  assert(a.head->data == 4 && a.tail->data == 2 && a.head->next->data == 3 &&
         a.tail->prev->data == 3);
  assert(a.remove(4) == true && a.getSize() == 2 && a.size == 2 && a.head->data == 3 &&
         a.head->next->data == 2 && a.tail->data == 2 && a.tail->prev->data == 3 &&
         a.remove(1) == false && a.remove(3) == true && a.remove(2) == true && a.head == NULL &&
         a.tail == NULL);
}
int main(void) {
  testList();
  return EXIT_SUCCESS;
}
