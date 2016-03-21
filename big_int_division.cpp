#include "common.h"
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 1) {
            return dividend;
        }
        
        bool neg_flag = false;
        if ((dividend < 0 && divisor > 0) 
            || (dividend > 0 && divisor < 0)) {
                neg_flag = true;
        }
        long long l = dividend;
        long long da = divisor;
        pair<long long, long long> res = d(abs(l), abs(da));
        
        int r = neg_flag ? -res.first : res.first;
        return r;
    }
    
    pair<long long, long long> d(long long dividend, long long divisor) {
        if (dividend == 0) {
            return make_pair(0, 0);
        }
        pair<long,long> t = d(dividend >> 1, divisor);
        
        t.first <<= 1;
        t.second <<= 1;
        
        if (dividend % 2) {
            t.second += 1;
        }
        
        if (t.second >= divisor) {
            t.first += 1;
            t.second -= divisor;
        }
        return t;
    }
};

int main() {
    Solution sol;
    int l = -2147483648;
    int d = -2147483648;
    
    long long ll = l;
    long long dd = d;

    cout<<sol.divide(abs(ll), abs(dd))<<endl;
}
