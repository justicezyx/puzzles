#include "common.h"
using namespace std;

class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 1));
        if (n <= 1) {
            return res;
        }
        
        int max_depth = n/2 - 1;
        for (int v = 1, depth = 0; depth <= max_depth; ++depth) {
            for (int i = depth; i < n-depth; ++i) {
                res[depth][i] = v++;
            }
            for (int i = depth+1; i < n-depth; ++i) {
                res[i][n-depth-1] = v++;
            }
            for (int i = n-depth-2; i >= depth; --i) {
                res[n-depth-1][i] = v++;
            }
            for (int i = n-depth-2; i > depth; --i) {
                res[i][depth] = v++;
            }
        }
        if (n % 2 == 1) {
            res[max_depth+1][max_depth+1] = n*n;
        }
        return res;
    }
};

int main() {
    Solution solution;
    solution.generateMatrix(2);
}
