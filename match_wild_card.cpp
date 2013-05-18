#include "common.h"
using namespace std;

ass Solution {
    
public:
    bool isMatch(const char *s, const char *p) {
        int s_len = strlen(s);
        if (strlen(s) == 0) {
            while (*p != '\0') {
                if (*p != '*') {
                    return false;
                }
                ++p;
            } 
            return true;
        }
        
        string pattern;
        int star_count = 0;
        while (*p) {
            pattern.push_back(*p);
            if (*p == '*') {
                ++star_count;
                while (*(++p) == '*');
            } else {
                ++p;
            }
        }

        // this is for the trivial case that the string length is less than
        // the pattern excluding '*'. Need to pass the large test case.
        if (s_len < pattern.length() - star_count) {
            return false;
        }
        return isMatch_a(s, pattern.c_str());
    }
    bool isMatch_a(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int s_len = strlen(s);
        int p_len = strlen(p);
        // vector<vector<bool>> dp(s_len+1, vector<bool>(p_len+1, 0));
        vector<bool> dp1(p_len+1, false);
        vector<bool> dp2(p_len+1, false);
        
        dp1[0] = 1;
        for (int i = 1; i <= p_len && p[i-1] == '*'; ++i) {
            dp1[i] = 1;
        }
        
        for (int i = 1; i <= s_len; ++i) {
            if (p[0] == '*') {
                dp2[1] = true;
            } else if (p[0] == '?' || p[0] == s[i-1]) {
                dp2[1] = (i == 1);
            } else {
                dp2[1] = false;
            }
            for (int j = 2; j <= p_len; ++j) {
                if (p[j-1] == '*') {
                    // originally I though this needs to look up all the
                    // dp stages forr i \in [0,i], since '*' can match arbitrary 
                    // length of suffix of string 's'.
                    // Turns out if consider it closely, if some prefix of s[0...i]
                    // matches p[0...j], the entire 's' will match p[0...j]. 
                    // No mater what we do, it's will be the same result, so just keep
                    // the last one.
                    dp2[j] = dp1[j] || dp2[j-1];
                } else if (p[j-1] == '?' || p[j-1] == s[i-1]) {
                    dp2[j] = dp1[j-1];
                }
            }
            swap(dp1, dp2);
            // dp2 needs to be cleared to be used in the next iteration.
            dp2.clear();
            dp2.resize(dp1.size());
        }
        return dp1[p_len];
    }
};

int main() {
    Solution solution;
    cout<<solution.isMatch("a", "a*");
}
