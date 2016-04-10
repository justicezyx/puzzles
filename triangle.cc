class Solution {
    std::vector<std::vector<int>> table;
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        table.clear();
        int m = triangle.size();
        if (m == 0) {
            return 0;
        }
        
        table.resize(m);
        for (int i = 0; i < m; ++i) {
            table[i].resize(i+1, std::numeric_limits<int>::max());
        }
        
        return min_sum_path(triangle, 0, 0, triangle.size());
    }
    
    int min_sum_path(const std::vector<std::vector<int>>& tr, int i, int j, int m) {
        if (i >= m) {
            // NULL node
            return 0;
        }
        
        int t = table[i][j];
        if (t != std::numeric_limits<int>::max()) {
            return t;
        }
        
        int min_l = min_sum_path(tr, i+1, j, m);
        int min_r = min_sum_path(tr, i+1, j+1, m);
        int min = tr[i][j] + std::min(min_l, min_r);
        
        table[i][j] = min;
        
        return min;
    }
};
