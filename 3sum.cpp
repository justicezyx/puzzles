class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());
        vector<vector<int>> res;
        for (int i = 0; i < num.size(); ++i) {
            if (i != 0 && num[i] == num[i-1]) {
                continue;
            }
            int v = num[i];
            int v_ = -v;
            vector<pair<int,int>> two_sums = two_sum(v_, num.begin() + i + 1, num.end());
            for (int j = 0; j < two_sums.size(); ++j) {
                vector<int> tmp;
                tmp.reserve(3);
                tmp.push_back(v);
                tmp.push_back(two_sums[j].first);
                tmp.push_back(two_sums[j].second);
                res.push_back(tmp);
            }
        }
        return res;
    }
    typedef vector<int>::iterator itor_t;
    vector<pair<int,int>> two_sum(int k, itor_t begin, itor_t end) {
        --end;
        vector<pair<int,int>> res;
        for (itor_t l = begin, r = end ; l < r; ) {
            int sum = *l + *r;
            if (sum == k) {
                if (l != begin && *l == *(l-1) && 
                    r != end && *r == *(r+1)) {
                    
                } else {
                    res.push_back(make_pair(*l, *r));
                }
                ++l, --r;
            } else if (sum < k) {
                ++l;
            } else {
                --r;
            }
        }
        return res;
    }
};
