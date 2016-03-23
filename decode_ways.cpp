#include "common.h"
using namespace std;

/**
 * Decode WaysJun 25 '12890 / 3442
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 *
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the total number of ways to decode it.
 */
class Solution {
public:
    int numDecodings(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.empty()) {
            return 0;
        }
        
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        
        // dp is the decoding way for the prefix of 's' of length 'i'
        for (int i = 1; i <= s.size(); ++i) {
            int num = 0;
            for (int j = i - 1; j >= 0 && i-j <= 2; --j) {
                if (is_valid_encoding(s.substr(j, i-j))) {
                    num += dp[j];
                }
            }
            dp[i] = num;
        }
        return dp[s.size()];
    }
    
    bool is_valid_encoding(const string& str) {
        if (str.empty() || str.size() > 2) {
            return false;
        }
        if (str.front() == '0') {
            return false;
        }
        istringstream iss(str);
        int tmp;
        iss >> tmp;
        if (tmp < 1 || tmp > 26) {
            return false;
        }
        return true;
    }
};

int main() {
    Solution solution;
    std::cout<<solution.numDecodings("10")<<std::endl;
}
