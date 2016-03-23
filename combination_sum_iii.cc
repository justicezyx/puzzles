#include <iostream>
#include <vector>
#include <algorithm>

void recursion(
    const std::vector<int>& nums, int pos, int partial_sum, int n, int target,
    std::vector<int>& partial, std::vector<std::vector<int>>& result) {

  if (partial_sum == target && partial.size() == n) {
    result.push_back(partial);
    return;
  }
  if (pos >= nums.size()) {
    return;
  }
  if (partial_sum > target) {
    return;
  }
  if (partial.size() >= n) {
    return;
  }

  recursion(nums, pos+1, partial_sum, n, target, partial, result);

  partial_sum += nums[pos];
  partial.push_back(nums[pos]);
  recursion(nums, pos+1, partial_sum, n, target, partial, result);
  partial.pop_back();
}

std::vector<std::vector<int>>
combination_sum(const int n, const int target) {
  std::vector<int> nums({1,2,3,4,5,6,7,8,9});
  std::vector<std::vector<int>> result;
  std::vector<int> partial;

  recursion(nums, 0, 0, n, target, partial, result);

  return result;
}

int main() {
  auto result = combination_sum(3, 9);
  for (const auto& combination : result) {
    for (const auto& num : combination) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}
