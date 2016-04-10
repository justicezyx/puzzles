#include <iostream>
#include <cassert>

int times(int x, int y) {
    // give the value of x * y

    if (!x || !y) {
        return 0;
    }

    assert(x > 0);
    assert(y > 0);

    int res = 0;
    while(x) {
        if (x % 2) res += y;
        y += y;
        x >>= 1;
    }
    return res;
}

void test() {
    std::cout<<times(10, 10)<<std::endl;
}

int main() {
    test();
}
