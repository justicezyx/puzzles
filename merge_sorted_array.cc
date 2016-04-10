/**
 * Merge Sorted ArrayMay 20 '12982 / 2221
 * Given two sorted integer arrays A and B, merge B into A as one sorted array.
 *
 * Note:
 * You may assume that A has enough space to hold additional elements from B. The number of elements initialized in A and B are m and n 
 */
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        int i = m - 1;
        int j = n - 1;
        for (int k = m+n-1; i >= 0 && j >= 0; --k) {
            if (A[i] > B[j]) {
                A[k] = A[i];
                --i;
            } else {
                A[k] = B[j];
                --j;
            }
        }
        if (j >= 0) {
            for (int k = 0; k <= j; ++k) {
                A[k] = B[k];
            }
        }
    }
};
