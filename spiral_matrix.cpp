class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> res;
        int m = matrix.size();
        if (m <= 0) {
            return res;
        }
        int n = matrix[0].size();
        res.reserve(m * n);
        
        int min_width = min(m, n);
        int max_depth = min_width / 2 - 1;
        for (int depth = 0; depth <= max_depth; ++depth) {
            for (int i = depth; i <= n - depth - 1; ++i) {
                res.push_back(matrix[depth][i]);
            }
            for (int i = depth + 1; i <= m-depth-1; ++i) {
                res.push_back(matrix[i][n-depth-1]);
            }
            for (int i = n-depth-2; i >= depth; --i) {
                res.push_back(matrix[m-depth-1][i]);
            }
            for (int i = m-depth-2; i > depth; --i) {
                res.push_back(matrix[i][depth]);
            }
        }
        if (min_width % 2 == 1) {
            if (m > n) {
                for (int i = max_depth+1; i <= m-max_depth-2; ++i) {
                    res.push_back(matrix[i][max_depth+1]);
                }
            } else if (m < n) {
                for (int i = max_depth+1; i <= n-max_depth-2; ++i) {
                    res.push_back(matrix[max_depth+1][i]);
                }
            } else {
                res.push_back(matrix[max_depth+1][max_depth+1]);
            }
        }
        return res;
    }
};
