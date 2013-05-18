/**
 * You are given an n x n 2D matrix representing an image.
 *
 * Rotate the image by 90 degrees (clockwise).
 *
 * Follow up:
 * Could you do this in-place?
 */
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = matrix.size();
        if (n <= 1) { 
            return;
        }
        int max = n/2 - 1;
        for (int i = 0; i <= max; ++i) {
            rotate_border(matrix, i, n);
        }
    }
    
    void rotate_border(vector<vector<int>>& matrix, int depth, int n) {
        for (int i = depth; i < n - depth-1; ++i) {
            swap(matrix[depth][i], matrix[i][n-depth-1]);
            swap(matrix[depth][i], matrix[n-depth-1][n-i-1]);
            swap(matrix[depth][i], matrix[n-i-1][depth]);
        }
    }
};

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = matrix.size();
        if (n <= 1) { 
            return;
        }
        int max = n/2 - 1;
        for (int i = 0; i < n; ++i) {
            for (int col = 0; col <= max; ++col) {
                swap(matrix[i][col], matrix[i][n-col-1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                swap(matrix[i][j], matrix[n-j-1][n-i-1]);
            }
        }
    }
};
