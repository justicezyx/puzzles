// Find the median of multiple sorted integer streams. An integer stream only
// provides the following methods:
//
// int GT(int v);  // returns the # of integers that are greater than |v|.
// int GET(int v);  // returns the # of integers that are greater than or equal
// to |v|.
// int LT(int v);  // returns the # of integers that are less than |v|.
// int LET(int v);  // returns the # of integers that are greater than or equal
// to |v|.

#include "common/assert.h"

#include <vector>
#include <iterator>

class IntegerStream {
  public:
    IntegerStream(std::vector<int> input) : sorted_nums_(std::move(input)) {}

    int GT(int v) const {
      return std::distance(
          std::upper_bound(sorted_nums_.begin(), sorted_nums_.end(), v),
          sorted_nums_.end());
    }
    int GET(int v) const {
      return std::distance(
          std::lower_bound(sorted_nums_.begin(), sorted_nums_.end(), v),
          sorted_nums_.end());
    }

    int LT(int v) const {
      return std::distance(
          sorted_nums_.begin(),
          std::lower_bound(sorted_nums_.begin(), sorted_nums_.end(), v));
    }

    int LET(int v) const {
      return std::distance(
          sorted_nums_.begin(),
          std::upper_bound(sorted_nums_.begin(), sorted_nums_.end(), v));
    }

    int min() const {
      return sorted_nums_.front();
    }

    int max() const {
      return sorted_nums_.back();
    }

    int size() const {
      return sorted_nums_.size();
    }

  private:
    std::vector<int> sorted_nums_;
};

void test_IntegerStream() {
  IntegerStream stream({1, 2, 3, 4, 5});
  EXPECT_EQ(4, stream.GT(1));
  EXPECT_EQ(5, stream.GET(1));
  EXPECT_EQ(0, stream.LT(1));
  EXPECT_EQ(1, stream.LET(1));
}

int max(const std::vector<IntegerStream>& streams) {
  int result = streams.front().max();
  for (const auto& s : streams) {
    result = std::max(result, s.max());
  }
  return result;
}

int min(const std::vector<IntegerStream>& streams) {
  int result = streams.front().min();
  for (const auto& s : streams) {
    result = std::min(result, s.min());
  }
  return result;
}

// Returns the # of numbers less than v and larger than v.
std::pair<int, int> Rank(const std::vector<IntegerStream>& streams, int v) {
  int less = 0;
  int larger = 0;
  for (const auto& s : streams) {
    less += s.LT(v);
    larger += s.GT(v);
  }
  return std::make_pair(less, larger);
}

int TotalSize(const std::vector<IntegerStream>& streams) {
  int total = 0;
  for (const auto& s : streams) {
    total += s.size();
  }
  return total;
}

// Returns the value that is the kth of all values in all streams. k is 0-based.
int FindKth(const std::vector<IntegerStream>& streams, int k) {
  int total = TotalSize(streams);
  int num_less = k;
  int num_greater = total - k - 1;

  int left = min(streams);
  int right = max(streams);

  while (left < right) {
    int mid = (right + left) / 2;
    auto rank = Rank(streams, mid);
    if (rank.first <= num_less && rank.second <= num_greater) {
      return mid;
    }
    if (rank.first > num_less) {
      right = mid - 1;
    }
    if (rank.second > num_greater) {
      left = mid + 1;
    }
  }
  return left;
}

void test_FindKth() {
  EXPECT_EQ(2, FindKth({IntegerStream({1, 2, 3, 4, 5}),
        IntegerStream({6, 7, 8})}, 1));
  EXPECT_EQ(2, FindKth({IntegerStream({1, 2, 3, 4, 5})}, 1));
  EXPECT_EQ(1, FindKth({IntegerStream({1, 2, 3, 4, 5})}, 0));
  EXPECT_EQ(1, FindKth({IntegerStream({1, 1, 3, 4, 5})}, 0));
  EXPECT_EQ(1, FindKth({IntegerStream({1, 1, 3, 4, 5})}, 1));
}

std::pair<int, int> Median(const std::vector<IntegerStream>& streams) {
  int total = TotalSize(streams);
  if (total % 2 == 1) {
    int median = FindKth(streams, total/2);
    return std::make_pair(median, median);
  } else {
    return std::make_pair(FindKth(streams, total/2-1),
        FindKth(streams, total/2));
  }
}

void test_Median() {
  EXPECT_EQ(std::make_pair(3, 3), Median({IntegerStream({1, 2, 3, 4, 5})}));
  EXPECT_EQ(std::make_pair(2, 3),
      Median({
        IntegerStream({1, 2, 3, 4, 5}),
        IntegerStream({1, 2, 2, 4, 5}),
      }));
}

int main() {
  test_IntegerStream();
  test_FindKth();
  test_Median();
}
