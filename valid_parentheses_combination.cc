#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// Recursive helper.
void recursion(int n, int open, int close, std::string& partial, std::vector<std::string>& result);

// Returns the valid string for |n| pairs of '()'.
std::vector<std::string> valid_paren(int n) {
  std::vector<std::string> result;
  std::string partial;
  recursion(n, 0, 0, partial, result);
  return result;
}

void recursion(int n, int open, int close, std::string& partial, std::vector<std::string>& result) {
  if (close == n) {
    result.push_back(partial);
    return;
  }
  if (open < n) {
    partial.push_back('(');
    recursion(n, open+1, close, partial, result);
    partial.pop_back();
  }
  if (open > close) {
    partial.push_back(')');
    recursion(n, open, close+1, partial, result);
    partial.pop_back();
  }
}

int main(int argc, char* argv[]) {
  std::istringstream iss(argv[1]);
  int count;
  iss >> count;
  for (const auto& str : valid_paren(count)) {
    std::cout << str << std::endl;
  }
}
