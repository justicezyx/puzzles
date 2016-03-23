#include <iostream>
#include <vector>
#include <algorithm>

/*
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> partial;
        h(candidates, 0, partial, 0, target, res);
        return res;
    }

    void h(vector<int>& cand, int pos, vector<int> partial, int psum,
        int target, vector<vector<int>>& res) {

        if (psum == target) {
            res.push_back(partial);
            return;
        }
        if (pos >= cand.size()) {
            return;
        }
        h(cand, pos + 1, partial, psum, target, res);
        while (psum + cand[pos] <= target) {
            psum += cand[pos];
            partial.push_back(cand[pos]);
            h(cand, pos + 1, partial, psum, target, res);
        }
    }
};
*/

void recursion(
    const std::vector<int>& nums, int pos, int partial_sum, int target,
    std::vector<int>& partial, std::vector<std::vector<int>>& result) {

  if (partial_sum == target) {
    result.push_back(partial);
    return;
  }
  if (pos >= nums.size()) {
    return;
  }
  recursion(nums, pos+1, partial_sum, target, partial, result);
  int i = 0;
  while (partial_sum + nums[pos] <= target) {
    i++;
    partial_sum += nums[pos];
    partial.push_back(nums[pos]);
    recursion(nums, pos+1, partial_sum, target, partial, result);
  }
  while (i-- > 0) {
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
  auto result = combination_sum({1, 2, 3, 7}, 7);
  for (const auto& combination : result) {
    for (const auto& num : combination) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}
