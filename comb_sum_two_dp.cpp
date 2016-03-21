#include "common.h"
using namespace std;

class Solution {
public:
    typedef vector<int> res_t;
    typedef vector<res_t> res_list_t;
    typedef res_list_t::iterator res_list_itor_t;
    
    vector<vector<int>> combinationSum2(vector<int> &num, int target) {
        vector<res_list_t> dp(target+1);
        
        dp[0].push_back(res_t());
        
        sort(num.begin(), num.end());
        
        for (int i = 0; i < num.size(); ++i) {
            vector<res_list_t> dp2(target+1);
            
            int cur = num[i];
            int min = (i!=0&&num[i]==num[i-1]) ? 1 : 0;
            for (int j = target-cur; j >= min; --j) {
                int v = cur + j;
                res_list_t p_res = dp[j];
                
                for(res_list_itor_t k = p_res.begin();
                    k != p_res.end(); ++k) {
                    k->push_back(cur);
                    dp2[v].push_back(*k);
                }
            }
            
            for (int j = 0; j <= target; ++j) {
                dp[j].insert(dp[j].end(), dp2[j].begin(), dp2[j].end());
            }
        }
        return dp[target];
    }
    
};

int main() {
    vector<int> num;
    num.push_back(1);
    num.push_back(1);
    cout<<combinationSum2(num, 2).size()<<endl;
}

