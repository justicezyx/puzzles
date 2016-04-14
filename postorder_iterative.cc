#include "common/common.h"

#include <iostream>

struct node {
  node(int v) : data(v), left(nullptr), right(nullptr) {}

  int data;
  node* left;
  node* right;
};

std::ostream& operator<<(std::ostream& os, const node& n) {
  os << n.data << " ";
  return os;
}

std::vector<int> postorder_iterative(node* root) {
    std::vector<int> result;
    if (root == nullptr) {
        return result;
    }

    node* prev = nullptr;
    std::stack<node*> h;
    h.push(root);

    while (!h.empty()) {
      node* curr = h.top();
      if (prev == nullptr || prev->left == curr || prev->right == curr) {
        if (curr->left) {
          h.push(curr->left);
        } else if (curr->right) {
          h.push(curr->right);
        }
      } else if (curr->left == prev) {
        // Traversed left branch.
        if (curr->right) {
          h.push(curr->right);
        }
      } else {
        // All sub-trees are traversed.
        result.push_back(curr->data);
        h.pop();
      }
      prev = curr;
    }
    return result;
}

int main() {
  //       0
  //   -1      1
  // -2  -3  5   2
  auto* root = new node(0);
  auto* left = new node(-1);
  auto* right = new node(1);
  auto* node_minus_2 = new node(-2);
  auto* node_2 = new node(2);
  auto* node_minus_3 = new node(-3);
  auto* node_5 = new node(5);
  root->left = left;
  root->right = right;
  left->left = node_minus_2;
  left->right = node_minus_3;
  right->left = node_5;
  right->right = node_2;

  std::vector<int> res = postorder_iterative(root);
  puzzles::print(res.begin(), res.end());
}
