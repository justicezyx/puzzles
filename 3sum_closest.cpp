class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());

        int min = numeric_limits<int>::max();
        int closest;
        for (int i = 0; i < num.size() - 2 && min > 0; ++i) {
            int v = num[i];
            int closest_diff = two_sum_closest(num, i + 1, num.size(), target - v);
            if (abs(v + closest_diff - target) < min) {
                min = abs(v + closest_diff - target);
                closest = v + closest_diff;
            }
        }
        return closest;
    }

    int two_sum_closest(vector<int>& num, int begin, int end, int target) {
        int min = numeric_limits<int>::max();
        int closest;

        for (int i = begin, j = end - 1; i < j && min > 0; ) {
            int sum = num[i] + num[j];
            if (abs(sum - target) < min) {
                min = abs(sum - target);
                closest = sum;
            }
            if (sum < target) {
                ++i;
            } else if (sum > target) {
                --j;
            } else {
                break;
            }
        }
        return closest;
    }
};
