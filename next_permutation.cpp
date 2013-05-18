#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void next_permutation(std::vector<int>& val) {
    if (val.size() <= 1) {
        return;
    }

    // find the longest consecutive increasing array.
    int prev = val.front();
    typedef std::vector<int>::iterator itor;

    itor cur = val.begin();
    for (++cur; cur != val.end() && *cur >= prev; ++cur) {
        prev = *cur;
        // does nothing.
    }

    if (cur == val.end()) {
        // this is the largest one.
        return;
    }
        
    // cur is the one passed the increasing array.
    itor t = std::lower_bound(val.begin(), cur, *cur);
    std::swap(*t, *cur);
    
    typedef std::vector<int>::reverse_iterator ritor;
    ritor rb(cur);
    std::sort(rb, val.rend());
}

void print(const std::vector<int>& val) {
    std::copy(val.begin(), val.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;
}

void test() {
    std::vector<int> val;
    val.reserve(10);
    for (int i = 0; i < 3; i++) {
        val.push_back(10 - i - 1);
    }

    int v;
    while (true) {
        print(val);
        next_permutation(val);
    }
}

int main() {
    std::vector<int> val;
    val.reserve(10);
    for (int i = 0; i < 3; i++) {
        val.push_back(i);
    }

    print(val);
    std::sort(std::vector<int>::reverse_iterator(val.begin() + 2), val.rend());
    print(val);

    test();
}
