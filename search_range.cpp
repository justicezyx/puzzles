class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        std::pair<int*,int*> range = std::equal_range(A, A+n, target);
        int begin = range.first - A;
        int end = range.second - A - 1;
        if (begin > end) {
            begin = -1;
            end = -1;
        }
        std::vector<int> res;
        res.push_back(begin);
        res.push_back(end);
        return res;
    }
};
