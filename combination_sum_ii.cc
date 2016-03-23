#include <iostream>
#include <vector>
#include <algorithm>

void recursion(
    const std::vector<int>& nums, int pos, int partial_sum, int target,
    std::vector<int>& partial, std::vector<std::vector<int>>& result) {

  if (partial_sum > target) {
    return;
  }
  if (partial_sum == target) {
    result.push_back(partial);
    return;
  }
  if (pos >= nums.size()) {
    return;
  }

  int next_pos = pos;
  while (next_pos < nums.size() && nums[next_pos] == nums[pos]) {
    next_pos++;
  }

  recursion(nums, next_pos, partial_sum, target, partial, result);
  for (int i = 0; i < next_pos - pos; i++) {
    partial.push_back(nums[pos]);
    partial_sum += nums[pos];
    recursion(nums, next_pos, partial_sum, target, partial, result);
  }
  for (int i = 0; i < next_pos - pos; i++) {
    partial.pop_back();
  }
}

std::vector<std::vector<int>>
combination_sum(const std::vector<int>& nums, const int target) {
  auto nums_copy = nums;
  std::sort(nums_copy.begin(), nums_copy.end());
  std::vector<std::vector<int>> result;
  std::vector<int> partial;

  recursion(nums_copy, 0, 0, target, partial, result);

  return result;
}

int main() {
  auto result = combination_sum({10,1,2,7,6,1,5}, 8);
  for (const auto& combination : result) {
    for (const auto& num : combination) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}
