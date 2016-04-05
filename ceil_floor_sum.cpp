#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

// Given an array of double numbers, and a target integer value, return a list
// of integers that sum up equal to the input target value. Each integer is
// either the floor or the ceil of one double number in the input. And each
// double value's corresponding value can appear exactly once in the result.
//
// The returned result should have the minimal difference with the original
// value.
//
// Input double array x_i for i in [0, n); find y_i for i in [0, n), y_i can be
// either floor(x_i) or ceil(x_i), and sum(y_i) == target. The result should
// have the minimal sum of the difference between x_i and y_i,
// min(sum(|y_i - x_i|)
//
// The solution is to determine the # of numbers that need to be floor or ceil
// based on the difference between the target and the maximal possible sum of
// y_i. The maximal sum(y_i) is sum(ceil(x_i)). The difference gives the # of
// numbers that must be floor.
//
// Then do a sorting of the difference of floored numbers to the original
// numbers, and pick the ones that are minimal and make them the floored values.
//
// Returns a list of pairs of <i, y_i, x_i>
std::vector<std::tuple<int, int, double>> min_abs_diff_floor_ceil_sum(
    const std::vector<double>& nums, int target) {
  std::vector<std::tuple<int, int, double>> result;
  if (nums.empty()) {
    return result;
  }

  // Each pair is <index, value>, so to keep the value's original index.
  std::vector<std::pair<int, double>> floor_diff_with_index;
  int ceil_sum = 0;
  for (int i = 0; i < nums.size(); i++) {
    floor_diff_with_index.push_back(
        std::make_pair(i, nums[i] - floor(nums[i])));
    ceil_sum += ceil(nums[i]);
  }

  int floor_count = ceil_sum - target;
  if (floor_count < 0 or floor_count > nums.size()) {
    // The value is either too big or too smaller.
    return result;
  }

  std::sort(
      floor_diff_with_index.begin(), floor_diff_with_index.end(),
      [](const std::pair<int, double>& lhs, const std::pair<int, double>& rhs) {
        return lhs.second < rhs.second;
      });
  result.reserve(nums.size());
  for (int i = 0; i < floor_count; i++) {
    int idx = floor_diff_with_index[i].first;
    double original = nums[floor_diff_with_index[i].first];
    result.push_back(std::tuple<int, int, double>{idx, floor(original), original});
  }
  for (int i = floor_count; i < nums.size(); i++) {
    int idx = floor_diff_with_index[i].first;
    double original = nums[floor_diff_with_index[i].first];
    result.push_back(std::tuple<int, int, double>{idx, ceil(original), original});
  }
  std::sort(
      result.begin(), result.end(), [](
        const std::tuple<int, int, double>& lhs,
        const std::tuple<int, int, double>& rhs) {
      return std::get<0>(lhs) < std::get<0>(rhs);
      });
  return result;
}

int main() {
  auto result = min_abs_diff_floor_ceil_sum({3.4, 4.6}, 8);
  for (const auto v :result) {
    std::cout << std::get<2>(v) << " : " << std::get<1>(v) << std::endl;
  }
}
