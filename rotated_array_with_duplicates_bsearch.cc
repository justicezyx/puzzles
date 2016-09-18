// Search in rotated sorted array with duplicates.

#include "common/assert.h"

#include <vector>

bool search(const std::vector<int>& nums, int target) {
  int l = 0, r = nums.size();

  while (l < r) {
    int mid = (l + r) / 2;
    if (nums[mid] == target) {
      return true;
    }

    if (nums[l] < nums[mid]) {
      // The left half does not have rotation.
      if (target >= nums[l] && target < nums[mid]) {
        r = mid;
      } else {
        l = mid +1;
      }
    } else if (nums[l] > nums[mid]) {
      // The left half does have rotation.
      if (target > nums[mid] && target <= nums[r-1]) {
        l = mid + 1;
      } else {
        r = mid;
      }
    } else {
      while (nums[++l] == nums[mid] && l < mid) {}
    }
  }
  return false;
}

void test() {
  EXPECT_FALSE(search({1, 1, 1, 4}, 2));
  EXPECT_TRUE(search({1, 2, 1, 1}, 2));
}

int main() {
  test();
}
