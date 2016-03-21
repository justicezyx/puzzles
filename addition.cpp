#include <iostream>
#include <cassert>

#include "common.h"

int inc(int x) {
    // return x + 1
    int c = 1;
    int p = 1;
    while (c) {
        if (!(x & p)) {
            c = 0;
        }
        x ^= p;
        p <<= 1;
    }
    return x;
}
    
// Adds two integers |x| and |y| without +.
int add(int x, int y) {
    assert(x >= 0);
    assert(y >= 0);

    if (x == 0) {
        return y;
    }
    if (y == 0) {
        return x;
    }

    int t = add(x >> 1, y >> 1);
    if (x % 2 && y % 2) {
        t = inc(t);
    }
    t <<= 1;
    if ((x & 1) ^ (y & 1)) {
        t = inc(t);
    }
    return t;
}

int add2(int x, int y) {
    assert(x >= 0);
    assert(y >= 0);
    
    if (x == 0) { return y; }
    if (y == 0) { return x; }

    int c = 0;
    int p = 1;
    int res = 0;
    while (x || y || c) {
        if ((x & 1) ^ (y & 1)) {
            // differ
            if (c) {
                res &= ~p;
                c = 1;
            } else {
                res |= p;
                c = 0;
            }
        } else if (!(x & 1) && !(y & 1)) {
            // both are 0.
            if (c) {
                res |= p;
                c = 0;
            } else {
                res &= ~p;
                c = 0;
            }
        } else if ((x & 1) && (y & 1)) {
            if (c) {
                res |= p;
            } else {
                res &= ~p;
            }
            c = 1;
        }

        x >>= 1;
        y >>= 1;
        p <<= 1;
    }
    return res;
}

    
void test() {
    for (int i = 0; i < 1000; i++) {
        if (inc(i) != i + 1) { 
            std::cout<<"wrong: "<<inc(1)<<std::endl;
        }
    }

    for (int i = 0; i < 1000; i++) {
        int a = rand() % 100;
        int b = rand() % 100;
        if (add(a, b) != a + b) {
            cout<<"custom: "<<add(a, b)<<" res:"<<a + b<<endl;
        }
        if (add2(a, b) != a + b) {
            cout<<"custom2: "<<add2(a, b)<<" res:"<<a + b<<endl;
        }
    }
}

int main() {
    test();
}
