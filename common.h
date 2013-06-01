#ifndef COMMON_H
#define COMMON_H

#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include <cassert>
#include <iterator>
#include <stack>
#include <set>
#include <queue>
#include <unordered_map>
using namespace std;

template <typename ValueType>
ValueType convert(const char* text) {
    std::istringstream iss(text);
    ValueType res;
    iss>>res;
    return res;
}

bool has_enough_arg(int arg_num, int argc, const char* text) {
    if (argc < arg_num) {
        printf("%s, only:%d\n", text, argc);
        return false;
    }
    return true;
}
    
void test_has_enough_arg() {
    has_enough_arg(10, 4, "pass");
    has_enough_arg(1, 4, "pass is not show");
}

template<typename Iterator>
void print(Iterator begin, Iterator end) {
    typedef typename Iterator::value_type value_type;
    std::copy(begin, end, std::ostream_iterator<value_type>(std::cout, " "));
    std::cout<<std::endl;
}

template<typename T>
void print(T* begin, T* end) {
    std::copy(begin, end, std::ostream_iterator<T>(std::cout, " "));
    std::cout<<std::endl;
}

template<typename T>
void print(const T& data) {
    std::cout<<data<<std::endl;
}

template<typename T0, typename T1, typename T2>
void print(const T0& data0, const T1& data1, const T2& data2) {
    std::cout<<data0<<data1<<data2<<std::endl;
}

int rnd() {
    int t = rand() % 12;
    if (t < 4) {
        return -t;
    } else if (t > 7) {
        return t;
    }
    return 0;
}

typedef int (*rndgen)();

std::vector<int> rnd_fill(int l, rndgen r) {
    std::vector<int> res;
    res.reserve(l);

    for (int i = 0; i < l; ++i) {
        res.push_back(r());
    }
    return res;
}

#endif
