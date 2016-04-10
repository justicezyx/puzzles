#include <iostream>
#include <cassert>

std::pair<int,int> divide(int x, int y) {
    // get the qutient and reminder of x / y
    // assume both will be positive numbers
    std::cout<<"x:"<<x<<" y:"<<y<<std::endl;
    assert(x >= 0);
    assert(y > 0);

    // recursively call.
    if (x == 0) {
        return std::make_pair(0, 0);
    }

    std::pair<int,int> t = divide(x>>1, y);
    t.first <<= 1;
    t.second <<= 1;
    
    if (x % 2) t.second += 1;
    if (t.second >= y) {
        t.first += 1;
        t.second -= y;
    }

    return t;
}

std::pair<int,int> general_divide(int x, int y) {
    assert(y != 0);
    if (x < 0 && y < 0) {
        std::pair<int,int> t = divide(-x, -y);
        return std::make_pair(t.first, -t.second);
    } else if (x < 0) {
        std::cout<<"x is less than 0"<<std::endl;
        std::pair<int,int> t = divide(-x, y);
        return std::make_pair(-t.first, -t.second);
    } else if (y < 0) {
        std::cout<<"x: "<<x<<" y: "<<y<<std::endl;
        std::pair<int,int> t = divide(x, -y);
        return std::make_pair(-t.first, t.second);
    }
    return divide(x, y);
}
        
void test() {
    std::pair<int,int> res = general_divide(-2147483648, 2);
    std::cout<<"res = general_divide(-12314, 12);"<<std::endl;
    std::cout<<res.first<<" "<<res.second<<std::endl;
}

std::pair<long,long> divide_recursive(long dividend, long divisor);

int gendivide(int dividend, int divisor) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (divisor == 1) {
        return dividend;
    }
    long top = dividend;
    long bot = divisor;
    std::pair<long,long> t = divide_recursive(labs(top), labs(bot));
    if ((top < 0 && bot > 0) || (top > 0 && bot < 0)) {
        return -t.first;
    }
    return t.first;
}

int main() {
    int val = -2147483648;
    long lv = val;
    // if (lv < 0) { lv = -lv; }
    int res = gendivide(val, 2);
    std::cout<<res<<std::endl;
}

std::pair<long,long> divide_recursive(long dividend, long divisor) {
    std::cout<<dividend<<" "<<divisor<<std::endl;
    if (dividend == 0) {
        return std::make_pair(0,0);
    }
    std::pair<long,long> t = divide_recursive(dividend >> 1, divisor);
    t.first <<= 1;
    t.second <<= 1;
    if (dividend % 2 != 0) {
        ++t.second;
    }
    if (t.second >= divisor) {
        t.second -= divisor;
        ++t.first;
    }
    return t;
}

/*
std::pair<int,int> divide(int x, int y) {
    // all non negative.
    assert(x >= 0);
    assert(y > 0);

    if (x == 0) {
        // this is the terminal case.
        return std::make_pair(0, 0);
    }

    std::pair<int,int> t = divide(x >> 1, y);
    
    t.first <<= 1;
    t.second <<= 1;
    
    if (x % 2) {
        t.second += 1;
    }

    if (t.second >= y) {
        t.first += 1;
        t.second -= y;
    }

    return t;
}
*/
