
/**
 * 000
 * 001
 * 011
 * 111
 * 110
 * 100
 * 101
 *
 * 000
 * 100
 * 101
 * 001
 * 011
 * 010
 * 110
 * 111
 *
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 * 111
 */

#include "common/common.h"

namespace puzzles {

class Solution {
public:
    vector<int> grayCode(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int count = 1 << n;
        vector<int> res;
        res.reserve(static_cast<size_t>(pow(2, n)));
        for (int i = 0; i < count; ++i) {
            res.push_back(i ^ (i >> 1));
        }
        return res;
    }
};

} // puzzles
