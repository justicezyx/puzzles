#include "common.h"
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<int>> is_par(s.size());
        for (int i = 0; i < s.size(); ++i) {
            is_par[i].resize(s.size(), 0);
            is_par[i][0] = 1;
        }
        
        vector<vector<string>> res;
        vector<string> partial;
        partition(s, 0, res, partial, is_par);
        return res;
    }
    
    void partition(const string& s, int begin, vector<vector<string>>& res, vector<string> partial, vector<vector<int>>& is_par) {
        std::cout<<s<<":"<<begin<<std::endl;
        if (begin >= s.size()) {
            res.push_back(partial);
            print(partial.begin(), partial.end());
            std::cout<<std::endl;
        }
        
        for (int i = begin; i < s.size(); ++i) {
            if (s[i] == s[begin] && (i - begin <= 1 || is_par[begin+1][i-begin-2])) {
                is_par[begin][i-begin] = 1;
            
                partial.push_back(s.substr(begin, i - begin + 1));
                partition(s, i + 1, res, partial, is_par);
                partial.pop_back();
            }
        }
    }
};

int main() {
    Solution s;
    s.partition("aaaa");
}
