#include "node.h"
using namespace std;
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {  //current node is sym
    assert(left == NULL && right == NULL);
    theMap.insert(pair<unsigned, BitString>(sym, b));
  }
  else {  //current node is not a sym
    assert(left != NULL && right != NULL);
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
