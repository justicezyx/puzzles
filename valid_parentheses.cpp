class Solution {
public:
    bool isValid(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<char> h1;
        stack<char> h2;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (isLeft(c)) {
                h1.push(c);
            } else if (isRight(c)) {
                h2.push(c);
                while (!h1.empty() && isRight(h1.top())) {
                    h2.push(h1.top());
                    h1.pop();
                }
                while (!h1.empty() && !h2.empty()) {
                    char t2 = h2.top();
                    h2.pop();
                    char t1 = h1.top();
                    h1.pop();
                    
                    if (!matchRight(t2, t1)) {
                        return false;
                    }
                }
            }
        }
        return h1.empty() && h2.empty();
    }
    bool isLeft(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool isRight(char c) {
        return c == ')' || c == ']' || c == '}';
    }
    bool matchRight(char c, char l) {
        switch (c) {
        case ')':
            return l == '(';
        case ']':
            return l == '[';
        case '}':
            return l == '{';
        default:
            return false;
        }
    }
    bool matchLeft(char c, char r) {
        switch (c) {
        case '(':
            return r == ')';
        case '[':
            return r == ']';
        case '{':
            return r == '}';
        default:
            return false;
        }
    }
};
