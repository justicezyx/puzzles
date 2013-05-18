class Solution {
public:
    bool isPalindrome(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (x < 0) {
            return false;
        }
        if (x <= 9) {
            return true;
        }
        int max_digit = 1;
        while (x / max_digit >= 10) {
            max_digit *= 10;
        }
        for (int i = 1, j = max_digit; i < j; i *= 10, j /= 10) {
            int a = (x / i) % 10;
            int b = (x / j) % 10;
            if (a != b) {
                return false;
            }
        }
        return true;
    }
};
