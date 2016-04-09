// Write another function that calculates the maximum profit with the additional
// constraint that you can only make 4 total trades (2 buys and 2 sells) in the
// month.

#include <iostream>
#include <vector>

// This question requires clarification, if we have the same restriction that we
// can only own at most 1 share at a time, then the problem is solved by finding
// the minimal of all prefix array and the maximal of all suffix array. And then
// iterate through the array and enumerate the sum of the potential differences.
//
// Here we assume that we can have either 1 transaction or 2 transaction. There
// requires a small trweak.
int max_profit_1(const std::vector<int>& prices) {
  if (prices.size() <= 1) {
    return 0;
  }

  if (prices.size() == 2) {
    if (prices.front() <= prices.back()) {
      return prices.back() - prices.front();
    } else {
      return 0;
    }
  }

  // The maximal profit if buy and sell inside [0, i] for i in
  // [0, prices.size()).
  std::vector<int> prefix_max_profit(prices.size());
  int min = prices.front();
  for (int i = 1; i < prices.size(); i++) {
    int max_profit = prices[i] - min;
    prefix_max_profit[i] = std::max(0, max_profit);
    min = std::min(min, prices[i]);
  }

  // The maximal profit if by and sell inside [i, prices.size()) for i in
  // [0, prices.size()).
  std::vector<int> suffix_max_profit(prices.size());
  int max = prices.back();
  for (int i = prices.size()-2; i >= 0; i--) {
    int max_profit = max - prices[i];
    suffix_max_profit[i] = std::max(0, max_profit);
    max = std::max(max, prices[i]);
  }

  // i will be the selling point of the first buy and sell pair.
  int max_profit = 0;
  for (int i = 1; i < prices.size()-2; i++) {
    max_profit = std::max(
        max_profit, prefix_max_profit[i]+suffix_max_profit[i+1]);
  }
  return std::max(
      max_profit, /* maximal if trade only once */ prefix_max_profit.back());
}

#define ASSERT_TRUE(predict) do { \
  if (!(predict)) { \
    std::cout << "FAILED: " << #predict << std::endl; \
  } else { \
    std::cout << "PASSED: " << #predict << std::endl; \
  } \
} while(false);

void test_max_profit_1() {
  ASSERT_TRUE(0 == max_profit_1({}));
  ASSERT_TRUE(1 == max_profit_1({0, 1}));
  ASSERT_TRUE(2 == max_profit_1({0, 1, 2}));
  ASSERT_TRUE(3 == max_profit_1({0, 1, 2, 3}));
}

// If we can buy twice before selling twice, then the problem is even simpler.
// Find the 2 minimal prices in prefix and 2 maximal in the suffix for all
// suffix. And return their differences.

int main() {
  test_max_profit_1();
}
