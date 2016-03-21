class Solution {
public:
    int numDistinct(string S, string T) {
        std::vector<int> dp(T.size() + 1);
        dp[0] = 1;
        for (int i = 0; i < S.size(); ++i) {
            for (int j = T.size(); j > 0; --j) {
                dp[j] = dp[j] + (S[i] == T[j - 1] ? dp[j-1] : 0);
            }
        }
        return dp[T.size()];
    }
};
