#include "common/common.h"

int binary_rand() {
    return rand() % 2;
}

int randn(int n) {
    while (true) {
        int res = 0;
        int t = n;
        while (t) {
            res = (res << 1) + binary_rand();
            t >>= 1;
        }

        if (res <= n) {
            return res;
        }
    }
}

void test() {
    int t = 1 << 1;
    while (t) {
        std::cout<<"iteration"<<std::endl;
        t >>= 1;
    }
}

int main() {
    test();
}
