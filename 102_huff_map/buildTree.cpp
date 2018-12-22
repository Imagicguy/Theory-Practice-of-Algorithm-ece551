#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t queue;

  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      queue.push(new Node(i, counts[i]));
    }
  }

  while (queue.size() > 1) {
    Node * node1 = queue.top();
    queue.pop();
    Node * node2 = queue.top();
    queue.pop();
    Node * parent = new Node(node1, node2);
    queue.push(parent);
  }
  return queue.top();
}
