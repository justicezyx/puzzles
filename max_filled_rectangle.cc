#include "common/common.h"

/**
 * A matrix filled with "1" and "0", find the maximum rectangle filled will all "1".
 */

int max_rectangle_histogram(const std::vector<int>& histogram);

int max_filled_rectangle(const std::vector<std::vector<int> >& matrix) {
    int m = matrix.size();
    if (m == 0) {
        return 0;
    }

    int n = matrix[0].size();
    std::vector<int> h(matrix[0].begin(), matrix[0].end());

    int max = max_rectangle_histogram(h);
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1) {
                h[j] = h[j] + 1;
            } else {
                h[j] = 0;
            }
        }
        max = std::max(max, max_rectangle_histogram(h));
    }

    return max;
}

int max_rectangle_histogram(const std::vector<int>& histogram) {
    if (histogram.size() == 0) {
        return 0;
    }

    if (histogram.size() == 1) {
        return histogram[0];
    }

    std::stack<std::pair<int,int> > h;
    h.push(std::make_pair(histogram[0], 0));

    // initially max is the size of the first bar.
    int max = 0;
    for ( int i = 1; i < histogram.size(); ++i) {
        int lb = i;
        while (!h.empty() && h.top().first > histogram[i]) {
            int top_size = h.top().first * (i - h.top().second);
            max = std::max(max, top_size);
            lb = h.top().second;
            h.pop();
        }   

        // Do not push if the top element is same height as the current one.
        if (h.empty() || h.top().first < histogram[i]) {
            h.push(std::make_pair(histogram[i], lb));
        }
    }   
    
    while (!h.empty()) {
        int top_size = h.top().first * (histogram.size() - h.top().second);
        max = std::max(max, top_size);
        h.pop();
    }   
    return max;
}

int maximalRectangle(std::vector<std::vector<int> > &matrix) {
    if (matrix.empty()) {
        return 0;
    }

    int n = matrix[0].size();
    std::vector<int> H(n);
    std::vector<int> L(n);
    std::vector<int> R(n, n);

    int ret = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        int left = 0, right = n;
        // calculate L(i, j) from left to right
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1) {
                ++H[j];
                L[j] = std::max(L[j], left);
            }
            else {
                left = j+1;
                H[j] = 0; L[j] = 0; R[j] = n;
            }
        }
        std::cout<<i<<"-th row: "; print(H.begin(), H.end());
        // calculate R(i, j) from right to right
        for (int j = n-1; j >= 0; --j) {
            if (matrix[i][j] == 1) {
                R[j] = std::min(R[j], right);
                ret = std::max(ret, H[j]*(R[j]-L[j]));
            }
            else {
                right = j;
            }
            std::cout<<"j:"<<j<<" R[j]:"<<R[j]<<" right:"<<right<<std::endl;
            std::cout<<j<<"-th column: "; print(R.begin(), R.end());
            std::cout<<j<<"-th column: "; print(L.begin(), L.end());
        }
    }

    return ret;
}

void test() {
    std::vector<std::vector<int> > matrix;
    int A[] = {0, 1, 1, 0};
    std::vector<int> a(A, A + sizeof(A) / sizeof(int));
    matrix.push_back(a);
    matrix.push_back(a);
    matrix.push_back(a);

    std::cout<<max_filled_rectangle(matrix)<<" "<<maximalRectangle(matrix)<<std::endl;
}

int main() {
    test();
}
