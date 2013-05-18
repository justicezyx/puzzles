#include "common.h"

/**
 * A matrix contains '1' and '0'. Find the rectangle inside this matrix that
 * composed only of '1', which has the maximum size.
 */
typedef std::vector<std::vector<char>> matrix_t;
int max_filled_rectangle(const matrix_t& matrix) {
    if (matrix.size() == 0) {
        return 0;
    }   

    int row = matrix.size();
    int col = matrix[0].size();

    std::vector<int> height(col, 0); 
    std::vector<int> left_boundary(col, 0); 
    std::vector<int> right_boundary(col, col - 1); 

    int max = 0;
    for (int i = 0; i < row; ++i) {
        int left = 0;
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == '1') {
                height[i] = height[i] + 1;
                left_boundary[i] = std::max(left, left_boundary[i]);
            } else {
                height[i] = 0;
                left = j + 1;
                left_boundary[j] = col - 1;
            }   
        }   

        int right = col - 1;
        for (int j = col - 1; j >= 0; --j) {
            if (matrix[i][j] == '1') {
                right_boundary[j] = std::min(right, right_boundary[i]);
            } else {
                right = j - 1;
                right_boundary[j] = col - 1;
            }   
        }   
        for (int j = 0; j < col; ++j) {
            max = std::max(max, height[j] * (right_boundary[j] - left_boundary[j] + 1));
        }   
    }   
    return max;
}
