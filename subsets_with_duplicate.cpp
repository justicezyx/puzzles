/**
 * Given a collection of integers that might contain duplicates, S, return all possible subsets.
 */

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> res;
        if (S.empty()) {
            return res;
        }
        sort(S.begin(), S.end());
        vector<int> partial;
        partial.reserve(S.size());
        
        generate_unique_subsets(S, 0, partial, res);
        return res;
    }
    
    void generate_unique_subsets(const vector<int>& S, int pos,
                                 vector<int>& partial, vector<vector<int>>& res) {
        res.push_back(partial);
        for (int i = pos; i < S.size(); ++i) {
            if (i != pos && S[i] == S[i-1]) {
                continue;
            }
            partial.push_back(S[i]);
            generate_unique_subsets(S, i+1, partial, res);
            partial.pop_back();
        }
    }
};
