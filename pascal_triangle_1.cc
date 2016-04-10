class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        std::vector<std::vector<int>> res;
        if (numRows == 0) {
            return res;
        }
        
        res.reserve(numRows);
        std::vector<int> prev(1, 1);
        res.push_back(prev);
        
        std::vector<int> cur;
        for (int i = 1; i < numRows; ++i) {
            cur.resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                int left = j - 1;
                int right = j;
                if (left < 0 || right >= i) {
                    cur[j] = 1;
                } else {
                    cur[j] = prev[left] + prev[right];
                }
            }
            res.push_back(cur);
            prev = cur;
        }
        return res;
    }
};
