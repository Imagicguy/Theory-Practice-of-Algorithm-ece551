#ifndef __bstSET_H__
#define __bstSET_H__
#include <iostream>

#include "set.h"
using namespace std;

template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;

    Node(T t) : key(t), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}

  BstSet(const BstSet & bset) : root(NULL) { assignmentHelper(bset.root); }

  void assignmentHelper(Node * current) {
    if (current != NULL) {
      add(current->key);
      assignmentHelper(current->left);
      assignmentHelper(current->right);
    }
  }

  ~BstSet() { freeHelper(root); }

  void freeHelper(Node * current) {
    if (current != NULL) {
      freeHelper(current->left);
      freeHelper(current->right);
      delete current;
    }
  }

  bool contains(const T & key) const {
    Node * node = root;
    while (node != NULL) {
      if (node->key == key) {
        return true;
      }
      else if (node->key > key) {
        node = node->right;
      }
      else {
        node = node->left;
      }
    }
    return false;
  }

  BstSet & operator=(const BstSet & bset) {
    if (this == &bset)
      return *this;
    freeHelper(root);
    root = NULL;
    assignmentHelper(bset.root);
    return *this;
  }

  void remove(const T & key) { root = removeHelper(root, key); }

  Node * removeHelper(Node * current, const T & key) {
    if (current == NULL)
      return current;

    if (key == current->key) {
      if (current->left == NULL) {
        Node * tmp = current->right;
        delete current;
        return tmp;
      }
      else if (current->right == NULL) {
        Node * tmp = current->left;
        delete current;
        return tmp;
      }
      else {
        Node * tmp = current->right;
        Node * parent = current;
        bool right_null = true;

        while (tmp->left != NULL) {
          parent = tmp;
          tmp = tmp->left;
          right_null = false;
        }

        current->key = tmp->key;

        if (right_null)
          parent->right = tmp->right;
        else
          parent->left = tmp->right;

        delete tmp;
        return current;
      }
    }
    else if (key < current->key) {
      current->left = removeHelper(current->left, key);
      return current;
    }
    else {
      current->right = removeHelper(current->right, key);
      return current;
    }
  }

  Node * add(Node * node, const T & key) {
    if (node == NULL) {
      Node * temp = new Node(key);
      return temp;
    }
    else if (node->key == key) {
      return node;
    }
    else if (node->key > key) {
      node->right = add(node->right, key);
      return node;
    }
    else {
      node->left = add(node->left, key);
      return node;
    }
  }
  void add(const T & key) {
    //if (contains(key)){
    //  return;
    //}
    //if check contain here would increase runtime
    root = add(root, key);
  }
};

#endif
