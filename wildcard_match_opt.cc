/**
 * Wildcard MatchingMar 16 '121068 / 4270
 * Implement wildcard pattern matching with support for '?' and '*'.
 *
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 *
 * The matching should cover the entire input s
 *
 * Some examples:
 * isMatch("aa","a") ? false
 * isMatch("aa","aa") ? true
 * isMatch("aaa","aa") ? false
 * isMatch("aa", "*") ? true
 * isMatch("aa", "a*") ? true
 * isMatch("ab", "?*") ? true
 * isMatch("aab", "c*a*b") ? false
 */
class Solution {
    
public:
    bool isMatch(const char *s, const char *p) {
        int s_len = strlen(s);
        if (s_len == 0) {
            while (*p) {
                if (*p != '*') {
                    return false;
                }
                ++p;
            } 
            return true;
        }
        
        int p_len = strlen(p);
        if (p_len == 0) {
            return false;
        }
        
        string pattern;
        pattern.reserve(p_len);
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
        if (s_len < pattern.length() - star_count) {
            return false;
        }
        return isMatch_a(s, s_len, pattern.c_str(), pattern.length());
    }
    bool isMatch_a(const char *s, int s_len, const char *p, int p_len) {
        int* mem = new int[2 * p_len];
        int* dp1 = mem;
        int* dp2 = mem + p_len;
        memset(mem, 0, sizeof(int) * 2 * p_len);
        
        for (int i = 0; p[i] == '*'; ++i) {
            dp1[i] = 1;
        }
        
        for (int i = 0; i < s_len; ++i) {
            char pc = p[0];
            char sc = s[i];
            if (pc == '*') {
                dp2[0] = true;
            } else if (pc == '?' || pc == sc) {
                dp2[0] = (i == 0);
            }
            for (int j = 1; j < p_len; ++j) {
                char pc = p[j];
                if (pc == '*') {
                    dp2[j] = dp1[j] || dp2[j-1];
                } else if (pc == '?' || pc == sc) {
                    dp2[j] = dp1[j-1];
                }
            }
            swap(dp1, dp2);
            memset(dp2, 0, sizeof(int) * p_len);
        }
        int res = dp1[p_len-1];
        delete mem;
        return res;
    }
};
