#include <iostream>
#include <vector>
#include <string>

#include "common.h"

std::vector<std::string> num_to_string(const std::vector<int>& num,
    const std::vector<std::string>& mapping) {

    typedef std::vector<int>::const_iterator itor;

    int str_len = num.size();
    std::vector<int> radix;
    radix.reserve(mapping.size());
    
    int res_size = 1;
    for (itor i = num.begin(); i != num.end(); ++i) {
        // num of chars can be selected on each position.
        int cur_radix = mapping[*i].size();
        radix.push_back(cur_radix);
        res_size *= cur_radix;
    }

    std::vector<int> idx(str_len, 0);
    std::vector<std::string> res;
    res.reserve(res_size);
    
    int n = 0;
    do {
        std::string tmp(str_len, 'a');
        for (int i = 0; i < str_len; i++) {
            tmp[i] = mapping[num[i]][idx[i]];
        }
        res.push_back(tmp);
        n++;

        int carry = 0;
        for (int i = 0; i < str_len; i++) {
            int tmp = carry + idx[i] + 1;
            carry = tmp / radix[i];
            idx[i] = tmp % radix[i];
            if (carry == 0) {
                break;
            }
        }
    } while (n < res_size);

    return res;
}
            
int test() {
    std::vector<std::string> mapping;
    mapping.push_back("abc");
    mapping.push_back("def");
    mapping.push_back("ghi");
    mapping.push_back("jkl");

    std::vector<int> num;
    num.push_back(0);
    num.push_back(1);
    
    std::vector<std::string> res = num_to_string(num, mapping);

    print(res.begin(), res.end()); 
    return 0;
} 

int main() {
    test();
}
