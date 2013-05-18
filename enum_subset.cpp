class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> res;
        if (S.empty()) {
            res.push_back(vector<int>());
            return res; 
        }
        if (S.size() == 1) {
            res.push_back(vector<int>());
            res.push_back(vector<int>(1, S[0]));
            return res;
        }
        
        sort(S.begin(), S.end());
        vector<int> partial;
        enum_subset_recursive(S, 0, partial, res);
        return res;
    }
    
    void enum_subset_recursive(vector<int>& S, int p, vector<int>& partial, vector<vector<int>>& res) {
        if (p >= S.size()) {
            res.push_back(partial);
            return;
        }
        
        enum_subset_recursive(S, p+1, partial, res);
        partial.push_back(S[p]);
        enum_subset_recursive(S, p+1, partial, res);
        partial.pop_back();
    }
};
