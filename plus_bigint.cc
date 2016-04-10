#include "common/common.h"
using namespace std;

vector<int> plusOne(vector<int> &digits) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int carry = 1;
    int i = 0;
    while (carry && i < digits.size()) {
        std::cout<<digits[i]<<std::endl;
        int v = digits[i] + carry;
        std::cout<<"v:"<<v<<std::endl;

        carry = v / 10;
        digits[i] = v % 10;
    }
    if (carry == 1) {
        digits.push_back(1);
    }
    return digits;
}

int main() {
    std::vector<int> num;
    num.push_back(9);
    plusOne(num);
    print(num.begin(), num.end());
}

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int carry = 1;
        int i = digits.size() - 1;
        while (carry && i >= 0) {
            int v = digits[i] + carry;
            carry = v / 10;
            digits[i] = v % 10;
            --i;
        }
        std::vector<int> res;
        res.reserve(digits.size() + 1);
        if (carry == 1) {
            res.push_back(1);
        }
        res.insert(res.end(), digits.begin(), digits.end());
        return res;
    }
};
