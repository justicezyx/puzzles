/**
 * Minimum Path SumMar 29 '12815 / 1746
 * Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
 *
 * Note: You can only move either down or right at any point in time.
 */
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = grid.size();
        if (m <= 0) {
            return 0;
        }
        int n = grid[0].size();
        if (n <= 0) {
            return 0;
        }
        
        vector<int> dp(n);
        dp[0] = grid[0][0];
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i-1] + grid[0][i];
        }
        for (int i = 1; i < m; ++i) {
            dp[0] = dp[0] + grid[i][0];
            for (int j = 1; j < n; ++j) {
                dp[j] = min(dp[j-1], dp[j]) + grid[i][j];
            }
        }
        return dp[n-1];
    }
};

