#include "common/common.h"

int find_local_min(const std::vector<int>& prices, int start);
int find_local_max(const std::vector<int>& prices, int start);

int maxProfit(std::vector<int> &prices) {
    int max = 0;
    for (int i = 0; i < prices.size(); ) {
        int min_pos = find_local_min(prices, i);
        int max_pos = find_local_max(prices, min_pos + 1);
        if (min_pos < max_pos && max_pos < prices.size()) {
            max += prices[max_pos] - prices[min_pos];
        }
        i = max_pos;
    }
    return max;
}

int find_local_min(const std::vector<int>& prices, int start) {
    int i = start;
    while (i + 1 < prices.size() && prices[i] >= prices[i+1]) {
        ++i;
    }
    return i;
}

int find_local_max(const std::vector<int>& prices, int start) {
    int i = start;
    while (i + 1 < prices.size() && prices[i] <= prices[i+1]) {
        ++i;
    }
    return i;
}

void test() {
    int A[] = {2,1,2,0,1};
    std::vector<int> i(A, A + 5);
    std::cout<<maxProfit(i)<<std::endl;
}

int main() {
    test();
}
