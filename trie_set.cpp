#include <iostream>
#include <map>
#include <string>

class Node {
  public:
  Node* Get(char c) {
    if (next_.find(c) == next_.end()) {
      return nullptr;
    }
    return next_[c];
  }

  bool IsTerminal() {
    return next_.empty();
  }

  std::map<char, Node*> next_;
};

void Print(Node* root) {
  if (root->next_.empty()) {
    std::cout << "null" << std::endl;
    return;
  }
  for (const auto& pair : root->next_) {
    std::cout << pair.first << ": ";
    Print(pair.second);
  }
}

bool Contains(Node* root, const std::string& s) {
  if (root == nullptr) {
    return false;
  }

  auto curr = root;
  for (auto c : s) {
    curr = curr->Get(c);
    if (curr == nullptr) {
      return false;
    }
  }
  return curr->IsTerminal();
}

Node* BuildForString(const std::string& s) {
  if (s.empty()) {
    return new Node();
  }
  Node* next = BuildForString(s.substr(1));
  Node* root = new Node();
  root->next_[s.front()] = next;
  return root;
}

Node* CopyAndAdd(Node* root, const std::string& s) {
  if (root->Get(s.front()) == nullptr) {
    Node* child_root = BuildForString(s.substr(1));
    Node* new_root = new Node();
    new_root->next_ = root->next_;
    new_root->next_[s.front()] = child_root;
    return new_root;
  } else {
    Node* child_root = CopyAndAdd(root->Get(s.front()), s.substr(1));
    root->next_[s.front()] = child_root;
    return root;
  }
}

int main() {
  Node node;
  Node next;

  node.next_['a'] = &next;
  if (node.Get('a') != &next) {
    std::cout << "error" << std::endl;
  }

  if (node.IsTerminal()) {
    std::cout << "error" << std::endl;
  }

  if (!next.IsTerminal()) {
    std::cout << "error" << std::endl;
  }

  if (!Contains(&node, "a")) {
    std::cout << "error" << std::endl;
  }

  if (Contains(&node, "ab")) {
    std::cout << "error" << std::endl;
  }

  Node* abcd = BuildForString("abcd");
  if (!Contains(abcd, "abcd")) {
    std::cout << "error" << std::endl;
  }
  if (Contains(abcd, "abcdc")) {
    std::cout << "error" << std::endl;
  }

  Node* empty = BuildForString("");
  if (!Contains(empty, "")) {
    std::cout << "error" << std::endl;
  }

  empty = CopyAndAdd(empty, "abcd");

  empty = CopyAndAdd(empty, "bcd");

  Print(empty);
  for (const auto& pair : empty->next_) {
    std::cout << pair.first << " " << pair.second << std::endl;
  }

  if (!Contains(empty, "abcd")) {
    std::cout << "error" << std::endl;
  }
}
