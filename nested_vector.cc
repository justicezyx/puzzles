#include <iostream>
#include <vector>

struct NestedVector {
  int value;
  std::vector<NestedVector*> next;
};

std::vector<int> Flatten(const std::vector<NestedVector*> list) {
  if (list.empty()) {
    return std::vector<int>();
  }

  typedef std::pair<const std::vector<NestedVector*>*, int> stack_node_t;
  std::stack<stack_node> stack;
  stack.push({&list, 0});

  while (!stack.empty()) {
    auto stack_node = stack.top();
    stack.pop();

    if (stack_node.second >= stack_node.first->size()) {
      continue;
    } else {
      stack_node.second++;
      while (!stack_node.first->next.empty()) {
        stack.push(stack_node);
      }
    }
  }
}
