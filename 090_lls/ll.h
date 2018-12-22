#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

class listOutOfBound : public std::exception
{
  virtual const char * what() const throw() { return "Index exceed list size"; }

} list_ofb;
template<typename T>
class LinkedList
{
 private:
  int size;
  class Node
  {
   public:
    T data;
    Node * prev;
    Node * next;
    Node(const T & num) : data(num), prev(NULL), next(NULL) {}
  };
  Node * head;
  Node * tail;

 public:
  Node * getHead() const { return head; }
  Node * getTail() const { return tail; }
  LinkedList() : size(0), head(NULL), tail(NULL) {}
  LinkedList(const LinkedList & rhs) : size(0), head(NULL), tail(NULL) {
    Node * temp = rhs.getHead();
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this == &rhs) {
      return *this;
    }
    while (head != NULL) {
      Node * temp = head->next;  //delete all nodes in this
      delete head;
      head = temp;
    }

    size = 0;
    Node * temp = rhs.head;
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  void addFront(const T & item) {
    Node * temp = new Node(item);
    if (getSize() == 0) {
      head = temp;
      tail = temp;
    }
    else {
      head->prev = temp;
      temp->next = head;
      head = temp;
    }
    size++;
  }
  void addBack(const T & item) {
    Node * temp = new Node(item);
    if (getSize() == 0) {
      head = temp;
      tail = temp;
    }
    else {
      tail->next = temp;
      temp->prev = tail;
      tail = temp;
    }
    size++;
  }
  bool remove(const T & item) {
    int curSize = getSize();
    head = remove_helper(item, head);
    return !(curSize == getSize());
  }

  Node * remove_helper(const T & item, Node * curNode) {
    if (curNode == NULL)
      return NULL;
    if (item == curNode->data) {
      Node * temp = curNode->next;
      delete curNode;
      size--;
      return temp;
    }
    curNode->next = remove_helper(item, curNode->next);
    return curNode;
  }

  T & operator[](int index) {
    if (index < 0 && index >= getSize()) {
      throw list_ofb;
    }
    Node * temp = head;
    while (index > 0) {
      temp = temp->next;
      index--;
    }
    return temp->data;
  }
  const T & operator[](int index) const {
    if (index < 0 && index >= getSize()) {
      throw list_ofb;
    }
    Node * temp = head;
    while (index > 0) {
      temp = temp->next;
      index--;
    }
    return temp->data;
  }
  int find(const T & item) const {
    Node * curr = head;
    int index = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      else {
        curr = curr->next;
        index++;
      }
    }
    return -1;
  }
  int getSize() const { return size; }
};

#endif
