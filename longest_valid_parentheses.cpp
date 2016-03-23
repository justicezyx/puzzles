#include "common.h"

/**
 * Find the longest sub string that forms a valid parentheses string
 * from an input string.
 * Eg: "(((())" return 4
 * "((((((()))))))" return 14
 */

using namespace std;

int longest_valid_parentheses(const string& s) {
    stack<int> pos;
    int max = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!pos.empty() && s[pos.top()] == '(' && s[i] == ')') {
            pos.pop();
            int tmp = (pos.empty() ? -1 : pos.top());
            int l = i - tmp;
            max = std::max(max, l);
        } else {
            pos.push(i);
        }
    }
    return max;
}

void test() {
    string s = "())(())";
    cout<<longest_valid_parentheses(s)<<endl;
}

int main() {
    test();
}
