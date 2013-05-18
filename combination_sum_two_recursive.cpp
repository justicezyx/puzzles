#include "common.h"
using namespace std;

vector<vector<int> > comb_sum_two(vector<int>& num, int target) {
    sort(num.begin(), num.end());
    vector<int> partial;
    vector<vector<int> > res;
    recursive_solve(num, 0, partial, 0, res);
    return res;
}

void recursive_solve(const vector<int>& num, int psum, vector<int>& pres, int pos, vector<vector<int> >& res) {
    if (psum == target) {
        res.push_back(pres);
        return;
    }
    if (pos >= num.size()) {
        return;
    }
    int npos = pos + 1;
    int cur = num[pos];
    while (npos < num.size() && num[npos] == cur) ++npos;
    int size = pres.size();
    recursive_solve(num, psum, pres, npos, res);
    pres.resize(size);
    
    for (int i = pos; i < npos; ++i) {
        psum += cur;
        if (psum > target) {
            return;
        }
        pres.push_back(cur);
        ++size;
        recursive_solve(num, psum, pres, npos, res);
        pres.resize(size);
    }
}
