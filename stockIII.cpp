#include "common.h"

/**
 * Return the maximum profit of stock tracking; which are restricted to at most
 * 2 transactions.  The stock can only be bought after the previous bought stock
 * is sold, if there is any.  However, the buying and selling of the stack can
 * happen on the same day.
 */
int max_profit(const std::vector<int>& prices) {
    std::vector<int> profits(prices.size(), 0);
    for (int i = 1, min = prices.front(), max_profit = 0; i < prices.size(); ++i) {
        max_profit = std::max(max_profit, prices[i] - min);
        min = std::min(min, prices[i]);
        profits[i] = max_profit;
    }
    print(profits.begin(), profits.end());

    int res = 0;
    for (int i = prices.size() - 2, max = prices.back(), max_profit = 0; i >= 0; --i) {
        max_profit = std::max(max_profit, max - prices[i]);
        max = std::max(max, prices[i]);
        res = std::max(res, profits[i] + max_profit);
    }
    return res;
}
        
void test() {
    int A[] = {1, 2,};
    std::vector<int> input(A, A + 2);
    std::cout<<max_profit(input);
}

int main() {
    test();
}
