class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> res;
        vector<int> partial;
        partial.reserve(num.size());
        sort(num.begin(), num.end());
        recursive_solve(num, 0, partial, 0, target, res);
        return res;
    }
    
    void recursive_solve(vector<int>& num, int psum, vector<int>& pres, int pos, int target, vector<vector<int>>& res) {
        if (psum == target) {
            res.push_back(pres);
            return;
        }
        if (pos >= num.size()) {
            return;
        }
        
        // The best solution is to treat this as same of repeating number unbounded.
        // That is, treat the repeatition count as the actual repeated count.
        for (int i = pos; i < num.size(); ++i) {
            if (i != pos && num[i] == num[i-1]) {
                continue;
            }
            pres.push_back(num[i]);
            // this has the problem that: the input arg 'pos' is the current candidate to be inserted.
            // although this for loop prevent from repating same number in this iteration.
            // In the recursive call following, the same number will be repeated.
            // The redundant recursive call is in the order of n^2.
            recursive_solve(num, psum+num[i], pres, i+1, target, res);
            pres.pop_back();
        }
    }
};
