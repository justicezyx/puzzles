#include "common.h"
using namespace std;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());
        vector<vector<int> > res;
        for (int i = 0; i < num.size(); ++i) {
            if (i != 0 && num[i] == num[i-1]) {
                continue;
            }
            int l = num[i];
            for (int j = num.size()-1; j > i+2; --j) {
                if (j != num.size()-1 && num[j] == num[j+1]) {
                    continue;
                }
                int r = num[j];
                int v = l + r;
                vector<pair<int,int> > twosums = two_sum(num, i+1, j, target - v);
                for (int i = 0; i < twosums.size(); ++i) {
                    vector<int> tmp;
                    tmp.reserve(4);
                    tmp.push_back(l);
                    tmp.push_back(twosums[i].first);
                    tmp.push_back(twosums[i].second);
                    tmp.push_back(r);
                    res.push_back(tmp);
                }
            }
        }
        return res;
    }
    
    vector<pair<int,int> > two_sum(const vector<int>& num, int begin, int end, int target) {
        vector<pair<int,int> > res;
        for (int i = begin, j = end - 1; i < j; ) {            
            int l = num[i];
            int r = num[j];
            int sum = l + r;
            if (sum < target) {
                ++i;
                // while (num[i] == l) ++i;
            } else if (sum > target) {
                --j;
                // while (num[j] == r) --j;
            } else {
                res.push_back(make_pair(l,r));
                ++i, --j;
                while (num[i] == l) ++i;
                while (num[j] == r) --j;
            }
        }
        return res;
    }
};
