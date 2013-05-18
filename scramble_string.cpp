class Solution {
public:
    bool isScramble(string s1, string s2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s1 == s2) {
            return true;
        }
        if (s1.size() != s2.size()) {
            return false;
        }
        
        string t1 = s1;
        string t2 = s2;
        
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        if (t1 != t2) {
            return false;
        }
        
        
        int s = s1.size();
        for (int i = 1; i <= s-1; ++i) {
            string left1 = s1.substr(0, i);
            string right1 = s1.substr(i, s-i);
            string left2 = s2.substr(0, i);
            string right2 = s2.substr(i, s-i);
            if (isScramble(left1, left2) && isScramble(right1, right2)) {
                return true;
            }
            
            string left3 = s2.substr(0, s-i);
            string right3 = s2.substr(s-i, i);
            if (isScramble(left1, right3) && isScramble(right1, left3)) {
                return true;
            }
        }
        return false;
    }
};
