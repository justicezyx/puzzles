/**
 * Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
 *
 * For example, given the array [−2,1,−3,4,−1,2,1,−5,4]:noh
 * the contiguous subarray [4,−1,2,1] has the largest sum = 6.
 *
 * More practice:
 * If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
 */
class Solution {
public:
    int maxSubArray(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int max = numeric_limits<int>::min();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (sum < 0) { sum = 0; }
            sum += A[i];
            max = std::max(max, sum);
        }
        return max;
    }
};
