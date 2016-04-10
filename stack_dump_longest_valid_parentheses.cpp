#include "common/common.h"

int longestValidParentheses(string s) {
    stack<int> pos;
    stack<int> len;
    
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            pos.push(i);
            len.push(0);
            cout<<"left"<<endl;
        } else {
            if (!pos.empty() && s[pos.top()] == '(') {
                cout<<"right match"<<endl;
                int l = i - pos.top() + 1;
                pos.pop();
                while (len.top() != 0) {
                    len.pop();
                }
                len.pop();
                len.push(l);
                cout<<"pushed "<<l<<endl;
            } else {
                cout<<"right"<<endl;
                len.push(0);
                pos.push(i);
            }
        }
    }
    int max = 0;
    int tmp = 0;
    while (!len.empty()) {
        cout<<len.top()<<" ";
        if (len.top() == 0) {
            max = std::max(max, tmp);
            tmp = 0;
        } else {
            tmp += len.top();
        }
        len.pop();
    }
    return max;
}

void test() {
    string s = "()(())";
    longestValidParentheses(s);
}

int main() {
    test();
}
