/** 
 * Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
 */
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int>> res;
        if (n == 0 || k == 0) {
            return res;
        }
        
        vector<int> partial;
        partial.reserve(k);
        
        selection(1, n+1, k, partial, res);
        return res;
    }
    
    void selection(int begin, int end, int k, vector<int>& partial, vector<vector<int>>& res) {
        if (k == 0) {
            res.push_back(partial);
            return;
        }
        
        if (end - begin < k) {
            return;
        }
        
        for (int i = begin; i < end; ++i) {
            partial.push_back(i);
            selection(i+1, end, k-1, partial, res);
            partial.pop_back();
        }
    }
};
