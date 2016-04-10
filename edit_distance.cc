/**
 * Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
 *
 * You have the following 3 operations permitted on a word:
 *
 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 */
class Solution {
public:
    int minDistance(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = word1.size();
        int n = word2.size();
        if (m == 0 || n == 0) {
            return max(m, n);
        }
        
        vector<int> dp(n+1, 0);
        vector<int> dp2(n+1, 0);
        for (int i = 0; i < n+1; ++i) {
            dp[i] = i;
        }
        
        for (int i = 0; i < m; ++i) { 
            for (int j = 0; j < n; ++j) {
                if (word1[i] == word2[j]) {
                    dp2[j+1] = dp[j];
                } else {
                    dp2[j+1] = min(dp[j+1], min(dp[j], dp2[j])) + 1;    
                }
            }
            dp = dp2;
            dp[0] = i+1;
            dp2[0] = i+1;
        }
        return dp[n];
    }
};
