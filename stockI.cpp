#include "common/common.h"

int max_profit(const std::vector<int>& prices) {
    if (prices.size() <= 1) {
        return 0;
    }

    if (prices.size() == 2) {
        return std::max(0, prices[1] - prices[0]);
    }

    int res = 0;
    for (int i = 1, min = prices.front(); i < prices.size(); ++i) {
        res = std::max(res, prices[i] - min);
        min = std::min(min, prices[i]);
    }
    return res;
}

void test() {
    int A[] = {1,2,4,2,5,7,2,4,9,0,9};
    std::vector<int> input(A, A + sizeof(A) / sizeof(int));
    // this should return 9;
    std::cout<<max_profit(input)<<std::endl;
}

int main() {
    test();
}
