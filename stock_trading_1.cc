// Write a function that computes the maximum profit for a list of stock prices.
// You can buy and sell the stock as many times as you want and there is no fee
// to buy or sell, but you can only own 1 share of the stock at a time (i.e.
// you must sell before you can buy again).
#include <iostream>
#include <vector>

// The selling point is at every local maximal, i.e., any price point where
// previous prices and later prices are lower.
//
// The buying point is the local minimal between the previous and current
// selling points.
int max_profit(const std::vector<int>& prices) {
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

  // This is the minimal price of the prices between the previous and current
  // selling point. At the beginning it is initialized to prices[0].
  //
  // We set the min value to a possible candidate so to avoid the confusion of
  // setting invalid values.
  int window_min = prices.front();
  int max_profit = 0;
  for (int i = 1; i < prices.size(); ) {
    if ((prices[i-1] <= prices[i] && i+1 >= prices.size()) ||
        (prices[i-1] <= prices[i] && prices[i] > prices[i+1])) {
      max_profit += (prices[i] - window_min);
      if (i+1 < prices.size()) {
        window_min = prices[i+1];
      }
      i += 2;
    } else {
      window_min = std::min(window_min, prices[i]);
      i++;
    }
  }
  return max_profit;
}

#define ASSERT_TRUE(predict) do { \
  if (!(predict)) { \
    std::cout << "FAILED: " << #predict << std::endl; \
  } else { \
    std::cout << "PASSED: " << #predict << std::endl; \
  } \
} while(false);

void test() {
  ASSERT_TRUE(0 == max_profit({}));
  ASSERT_TRUE(0 == max_profit({1}));
  ASSERT_TRUE(0 == max_profit({1, 0}));
  ASSERT_TRUE(1 == max_profit({0, 1}));
  ASSERT_TRUE(2 == max_profit({0, 1, 2}));
  ASSERT_TRUE(4 == max_profit({0, 1, 2, 0, 1, 2}));
  ASSERT_TRUE(4 == max_profit({0, 1, 2, 2, 0, 1, 2, 2}));
  ASSERT_TRUE(2 == max_profit({2, 2, 2, 0, 1, 2}));
  ASSERT_TRUE(2 == max_profit({2, 2, 2, 0, 1, 2, 2}));
}

int main() {
  test();

}
