/**
 * generate all unique subsets of an array of unique integers.
 * keep them in sorted order.
 */
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(S.begin(), S.end());
        vector<vector<int>> res;
        res.reserve(pow(2, S.size()));
        vector<int> partial;
        partial.reserve(S.size());
        
        generate_subsets(S, partial, 0, res);
        return res;
    }
    
    void generate_subsets(vector<int>& S, vector<int>& partial, int pos, vector<vector<int>>& res) {
        res.push_back(partial);
        for (int i = pos; i < S.size(); ++i) {
            partial.push_back(S[i]);
            generate_subsets(S, partial, i+1, res);
            partial.pop_back();
        }
    }
};
