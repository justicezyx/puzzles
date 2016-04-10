#include "common/common.h"

class Solution {
public:
    int search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (int left = 0, right = n - 1; left <= right; ) {
            int mid = left + (right - left)/2;
            if (A[mid] == target) { return mid; }
            // if (A[left] == target) { return left; }
            // if (A[left+len-1] == target) { return left+len-1; }
            
            // int left_len = len / 2;
            if (A[left] <= A[mid]) {
                // [left, mid] is sorted and target is inside
                if (A[left] <= target && A[mid] > target) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (A[mid] < target && A[right] >= target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    int A[] = {5, 1, 3};

    search(A, 3, 3);
}
