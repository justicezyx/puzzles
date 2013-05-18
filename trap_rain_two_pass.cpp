class Solution {
public:
    int trap(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n < 3) {
            return 0;
        }
        int max_idx = 0;
        int max = 0;
        for (int i = 0; i < n; ++i) {
            if (A[i] > max) {
                max_idx = i;
                max = A[i];
            }
        }
        int res = 0;
        for (int i = 0, partial = 0, left = 0; i <= max_idx; ++i) {
            if (A[i] >= A[left]) {
                // can preserve
                res += partial;
                left = i;
                partial = 0;
            } else {
                partial += A[left] - A[i];
            }
        }
        
        for (int i = n-1, partial = 0, right = n-1; i >= max_idx; --i) {
            if (A[i] >= A[right]) {
                res += partial;
                right = i;
                partial = 0;
            } else {
                partial += A[right] - A[i];
            }
        }
        return res;
    }
};
