class Solution {
public:
    bool isPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int i = 0;
        int j = s.size() - 1;
        
        while (i < j) {
            while(!isalnum(s[i]) && i <= j) { i++; }
            while(!isalnum(s[j]) && i <= j) { j--; }
            
            if (i < j && is_char(s[i]) && toupper(s[i]) != toupper(s[j])) {
                return false;
            }
            if (i < j && !is_char(s[i]) && s[i] != s[j]) {
                return false;
            }
            ++i; --j;
        }
        return true;
    }
    
    bool is_char(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
};
