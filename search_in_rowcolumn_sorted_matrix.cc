/**
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = matrix.size();
        if (m == 0) {
            return false;
        }
        int n = matrix[0].size();
        
        for (int i = m-1, j = 0; i >= 0 && j < n;) {
            int v = matrix[i][j];
            if (v == target) {
                return true;
            }
            if (v < target) {
                ++j;
            } else {
                --i;
            }
        }
        return false;
    }
};
