#include "common.h"

std::vector<int> get_sample(int total, int s) {
    std::vector<int> res;
    res.reserve(s);

    for (int i = 0; i < s; ++i) {
        res.push_back(i);
    }

    if (s >= total) {
        return res;
    }

    for (int i = s; i < total; ++i) {
        int t = rand() % total;
        if (t < s) {
            res[t] = i;
        }
    }

    return res;
}

void test() {
    srand(time(0));
    std::vector<int> res = get_sample(100, 10);
    print(res.begin(), res.end());
}

int main() {
    test();
}
