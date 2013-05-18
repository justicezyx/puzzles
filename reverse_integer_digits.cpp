class Solution {
public:
    int reverse(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (x < 0) {
            return -reverse(-x, 0);
        }
        return reverse(x, 0);
    }
    
    int reverse(int x, int d) {
        if (x == 0) {
            return d;
        }
        return reverse(x / 10, d * 10 + x % 10);
    }
};
