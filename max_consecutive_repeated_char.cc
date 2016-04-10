#include "common/common.h"
using namespace std;

/**
 * Find the list of chars that have the maximum consecutive repetitions.
 */
string solve(const string& str) {
    string res;
    for (int i = 0, j = 1, max_rep = 0, len = str.size(); i < len; i=j, j=i+1) {
        for (char c = str[i]; str[j] == c && j < len; ++j);
        if (j - i > max_rep) {
            max_rep = j - i;
            res.clear();
        } 
        if (j - i >= max_rep) {
            res.push_back(str[i]);
        }
    }
    return res;
}

void test() {
    string a = "this is a sentence";
    std::cout<<solve(a)<<std::endl;
    a = "thiss a  sseeentence";
    std::cout<<solve(a)<<std::endl;
}

int main() {
    test();
}
