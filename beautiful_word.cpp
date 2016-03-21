#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "common.h"
std::string most_beautiful_word(const std::string& str) {
    typedef std::string::iterator itor;
    int* count = new int[256]();
    bool* used = new bool[256]();
    print(count, count + 256);
    print(used, used + 256);

    std::vector<char> res;

    assert (count[0] == 0);
    for (int i = 0; i < str.size(); ++i) {
        ++count[str[i]];
    }
    
    for (int i = 0; i < str.size(); ++i) {
        if (used[str[i]]) {
            --count[str[i]];
            continue;
        }

        while (res.size() > 0 && count[res.back()] > 1 && str[i] < res.back()) {
            --count[res.back()];
            used[res.back()] = false;
            res.pop_back();
        }

        res.push_back(str[i]);
        used[str[i]] = true;
    }
        
    return std::string(res.begin(), res.end());
}
        
void test() {
    std::string input = "babab";
    std::cout<<most_beautiful_word(input)<<std::endl;
    input = "qpiejengtkwenfkjhwejkjqkwerhqjwehjkbghfhsajdhkjasdhflkjhwjeqbrjqwbeghjqegjkhgkjqhergiuregkwekjrgerg";
    std::cout<<most_beautiful_word(input)<<std::endl;
}

int main() {
    test();
}
