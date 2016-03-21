class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> partial;
        h(candidates, 0, partial, 0, target, res);
        return res;
    }

    void h(vector<int>& cand, int pos, vector<int> partial, int psum,
        int target, vector<vector<int>>& res) {

        if (psum == target) {
            res.push_back(partial);
            return;
        }
        if (pos >= cand.size()) {
            return;
        }
        h(cand, pos + 1, partial, psum, target, res);
        while (psum + cand[pos] <= target) {
            psum += cand[pos];
            partial.push_back(cand[pos]);
            h(cand, pos + 1, partial, psum, target, res);
        }
    }
};
