/**
 * Remove Duplicates from Sorted Array IIApr 19 '12652 / 1484
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?
 *
 * For example:noh
 * Given sorted array A = [1,1,1,2,2,3]:noh
 *
 * Your function should return length = 5, and A is now [1,1,2,2,3]
 */
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n <= 1) {
            return n;
        }
        
        int pos = 0;
        for (int i = 0; i < n; ) {
            int j = i+1;
            while (j < n && A[j] == A[i]) {
                ++j;
            }
            if (j-i > 2) {
                A[pos++] = A[i++];
                A[pos++] = A[i++];
            } else {
                for (int k = i; k < j; ++k) {
                    A[pos++] = A[k];
                }
            }
            i = j;
        }
        return pos;
    }
};
