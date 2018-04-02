#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order(const vector<Node>& tree, int key_index, vector<int> &in_order_result) {
  if (key_index == -1)
    return;
  in_order(tree, tree[key_index].left, in_order_result);
  in_order_result.push_back(tree[key_index].key);
  in_order(tree, tree[key_index].right, in_order_result);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if (tree.size() == 0)
    return true;
  vector<int> in_order_result;
  in_order(tree, 0, in_order_result);
  for (int i = 0; i < in_order_result.size()-1; i++) {
    if (in_order_result[i+1] < in_order_result[i])
      return false;
  }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
