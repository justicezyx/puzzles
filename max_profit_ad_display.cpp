/**
 * There are N slots for displaying M ads in total. 
 * Each ad has a given amount of profit; two adjacent slots cannot have the same ad.
 * Write a function to find the maximum profit by displaying ads on each slot.
 */

#include "common/common.h"
using namespace std;

int max_profit(int N, const vector<int>& P) {
    // M is the number of ads.
    int M = P.size();
    if (!N || !M) {
        return 0;
    }

    // A dp table, only need for the current slots for all the ads.
    // initialize it to be the profit in first slot.
    vector<int> dp(P.begin(), P.end());
    
    // prefix_max[i] stores the value of the prefix subarray ends at i-1.
    // prefix_max[0] is set to numeric_limits<int>::min() to be correct.
    vector<int> prefix_max(M);
    prefix_max[0] = numeric_limits<int>::min();

    // another table for storing the next slot's value.
    vector<int> dp2(M);
    
    // the profit at the beginning are the same as the profit.
    for (int i = 1; i < N; ++i) {
        print(dp.begin(), dp.end());

        for (int ad = 1; ad < M; ++ad) {
            prefix_max[ad] = max(prefix_max[ad-1], dp[ad-1]);
        }
            
        for (int ad = M-1, suffix_max = numeric_limits<int>::min(); ad >= 0; --ad) {
            int cur = ad+1 < M ? dp[ad+1] : numeric_limits<int>::min();
            suffix_max = std::max(cur, suffix_max);
            dp2[ad] = P[ad] + std::max(prefix_max[ad], suffix_max);
        }
        swap(dp, dp2);
    }
    
    int res = dp[0];
    for (int i = 1; i < M; ++i) {
        res = max(res, dp[i]);
    }
    return res;
}

void test() {
    int P[] = {12, 1, 5, 8};
    vector<int> profit(P, P + sizeof(P) / sizeof(int));
    int N = 1;
    cout<<max_profit(N, profit)<<endl;
}

int main() {
    test();
}
