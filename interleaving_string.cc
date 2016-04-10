#include "common/common.h"

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function  
        if (s3.size() != s1.size() + s2.size()) {
            return false;
        }
        if (s3.front() != s1.front() && s3.front() != s2.front()) {
            return false;
        }
        
        std::vector<std::vector<bool>> dp(s1.size() + 1);
        for (int i = 0; i < dp.size(); ++i) {
            dp[i].resize(s2.size() + 1, false);
        }
        dp[0][0] = true;
        for (int i = 0; i < s2.size(); ++i) {
            dp[0][i+1] = (s2[i] == s3[i]);
        }
        for (int i = 0; i < s1.size(); ++i) {
            dp[i+1][0] = (s1[i] == s3[i]);
        }
        for (int i = 0; i < s1.size(); ++i) {
            for (int j = 0; j < s2.size(); ++j) {
                bool t1 = (s1[i] == s3[i+j+1]) ? dp[i][j+1] : false;
                bool t2 = (s2[j] == s3[i+j+1]) ? dp[i+1][j] : false;
                dp[i+1][j+1] = (t1 || t2);
            }
        }
        return dp[s1.size()][s2.size()];
    }
};

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function  
        if (s3.size() != s1.size() + s2.size()) {
            return false;
        }
        if (s3.front() != s1.front() && s3.front() != s2.front()) {
            return false;
        }
        
        std::vector<int> dp2(s2.size() + 1);
        dp2[0] = true;
        for (int i = 0; i < s2.size(); ++i) {
            dp2[i+1] = (s2[i] == s3[i]) ? dp2[i] : false;
        }
        for (int i = 0; i < s1.size(); ++i) {
            dp2[0] = (s1[i] == s3[i]) ? dp2[0] : false;
            for (int j = 0; j < s2.size(); ++j) {
                bool t1 = (s1[i] == s3[i+j+1]) ? dp2[j+1] : false;
                bool t2 = (s2[j] == s3[i+j+1]) ? dp2[j] : false;
                dp2[j+1] = (t1 || t2);
            }
        }
        return dp2[s2.size()];
    }
};
