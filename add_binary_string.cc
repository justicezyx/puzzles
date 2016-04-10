class Solution {
public:
    string addBinary(string a, string b) {
        stack<char> res;
        for (int ai = a.size() - 1, bi = b.size() - 1, carry = 0;
             ai >= 0 || bi >= 0 || carry;
             --ai, --bi) {
            int a_num = 0;
            int b_num = 0;
            if (ai >= 0) {
                a_num = a[ai] - '0';
            }
            if (bi >= 0) {
                b_num = b[bi] - '0';
            }
            int v = a_num + b_num + carry;
            carry = v / 2;
            res.push(v % 2 + '0');
        }
        string str;
        while (!res.empty()) {
            str.push_back(res.top());
            res.pop();
        }
        return str;
    }
};
