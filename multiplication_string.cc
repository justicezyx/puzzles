class Solution {
public:
    string multiply(string a, string b) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> res(a.size() + b.size(), 0);
        for (int ai = a.size() - 1; ai >= 0; --ai) {
            int carry = 0;
            for (int bi = b.size() - 1; bi >= 0; --bi) {
                int a_num = a[ai] - '0';
                int b_num = b[bi] - '0';
                int pos = a.size() - 1 - ai + (b.size() - 1 - bi);
                int v = a_num * b_num + carry + res[pos];
                res[pos] = v % 10;
                carry = v / 10;
            }
            if (carry) {
                res[a.size() - 1 - ai + b.size()] = carry;
            }
        }
        
        string str;
        int i = res.size() - 1;
        while(i > 0 && res[i] == 0) {
            --i;
        }
        while(i >= 0) {
            str.push_back(res[i] + '0');
            --i;
        }
        return str;
    }
};
