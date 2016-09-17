// Given a list of non negative integers, arrange them such that they form the
// largest number.  For example, given [3, 30, 34, 5, 9], the largest formed
// number is 9534330.  Note: The result may be very large, so you need to return
// a string instead of an integer.

#include "common/assert.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string largest_number(const std::vector<int>& nums) {
  auto itoa = [](const int v) -> std::string {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  };

  std::vector<std::string> num_strs;
  num_strs.reserve(nums.size());

  for (const auto i : nums) {
    num_strs.push_back(itoa(i));
  }

  std::sort(num_strs.begin(), num_strs.end(),
            [](const std::string& lhs, const std::string& rhs) {
              return lhs + rhs > rhs + lhs;
            });

  auto result = std::accumulate(num_strs.begin(), num_strs.end(), std::string());
  auto begin = result.find_first_not_of('0');

  if (begin == std::string::npos) {
    return "0";
  } else {
    return result.substr(begin);
  }
}

int test() {
  EXPECT_EQ(std::string("0"), largest_number({0, 0}));
  EXPECT_EQ(std::string("4321"), largest_number({1, 2, 3, 4}));
}

int main() {
  test();
}
