class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &mat) { // dp on each row
        int m = mat.size();
        int n = mat[0].size();
        vector<int> r(n+1, 0);
        for (int i = 0; i < n && mat[0][i] == 0; ++i) {
            r[i+1] = 1;
        }
        
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                r[j+1] = (mat[i][j] == 1) ? 0 : r[j+1] + r[j];
            }
        }
        return r[n];
    }
};
