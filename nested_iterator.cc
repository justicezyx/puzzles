#include <iostream>
#include <vector>
#include <stack>

struct Iterator {
  Iterator* next;
  Iterator* nested;
  // Can have value only if nested is empty.
  int value;
};

std::vector<int> Flatten(Iterator* itor) {
  if (itor == nullptr) {
    return std::vector<int>();
  }

  std::stack<Iterator*> stack;
  while (itor != nullptr) {
    stack.push(itor);
    itor = itor->nested;
  }

  std::vector<int> result;

  while (!stack.empty()) {
    auto* curr = stack.top();
    stack.pop();
    if (curr->nested == nullptr) {
      result.push_back(curr->value);
    }

    curr = curr->next;
    while (curr != nullptr) {
      stack.push(curr);
      curr = curr->nested;
    }
  }
  return result;
}

// [1, [2, 3]]
int main() {
  Iterator a({nullptr, nullptr, 1});
  Iterator b({nullptr, nullptr, 2});
  Iterator c({nullptr, nullptr, 3});

  b.next = &c;

  Iterator d({nullptr, nullptr, 0});
  d.nested = &b;
  a.next = &d;

  auto result = Flatten(&a);
  for (const auto i : result) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
