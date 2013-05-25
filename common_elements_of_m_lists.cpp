/**
 * Find the common elements of m sorted lists.
 */

#include "common.h"

vector<int> common_elements(const vector<vector<int>>& lists) {
    vector<int> res;
    vector<int> idx(lists.size());

    bool finished = false;
    int count = 0;
    for (int max = numeric_limits<int>::min(); ; ) {
        for (int i = 0; i < idx.size(); ++i) {
            if (idx[i]  >= lists[i].size()) {
                finished = true;
                break;
            }
            int t = idx[i];
            while (lists[i][t] < max) {
                t++;
            }
            if (lists[i][t] == max) {
                count++;
            } else {
                max = lists[i][t];
                count = 1;
            }

            if (count == lists.size()) {
                res.push_back(lists[i][t]);
                count = 0;
                t++;
                max = lists[i][t];
            }             
            idx[i] = t;
        }
        if (finished) {
            break;
        }
    }
    return res;
}

void test() {
    vector<int> a{1, 2, 3, 4, 5, 7, 8};
    vector<int> b{-1, 1, 2, 5, 6, 8};
    vector<int> c{-1, 3, 4, 5, 7, 8};
    vector<int> d{};
    vector<vector<int>> lists {a, b, c, d};
    vector<int> res = common_elements(lists);
    print(res.begin(), res.end());
}

int main() {
    test();
}
