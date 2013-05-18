class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function    
        if (!s || !p) {
            return false;
        }
        
        if (*p == '\0' && *s == '\0') {
            return true;
        }
        
        if (*p == '\0' && *s != '\0') {
            return false;
        }
        char next = *(p + 1);
        if (next == '*') {
            if (isMatch(s, p+2)) {
                return true;
            }
            
            while (*s && (*p == '.' || *s == *p)) {
                if (isMatch(s + 1, p + 2)) {
                    return true;
                };
                ++s;
            }
        } else if ((is_char(*s) && *p == '.') || *s == *p) {
            return isMatch(s+1, p+1);
        }
        return false;
    }
    bool is_char(char c) {
        return c >= 'a' && c <= 'z';
    }
};
