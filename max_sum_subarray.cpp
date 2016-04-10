#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <numeric>

#include "common/common.h"

int max_sum_subarray(const std::vector<int>& input) {
    int max = std::numeric_limits<int>::min();
    for (int i = 0, sum = 0; i < input.size(); i++) {
        sum = sum + input[i];
        if (sum > max)
            max = sum;
        
        if (sum < 0)
            sum = 0;
    }
    return max;
}

std::vector<int> rnd_intvec(int l) {
    std::vector<int> res;
    res.reserve(l);

    srand(time(0));
    for (int i = 0; i < l; i++) {
        res.push_back(rand());
    }

    return res;
}

int bruteforce(const std::vector<int>& input) {
    int max = std::numeric_limits<int>::min();
    for (int i = 0; i < input.size(); i++) {
        int sum = 0;
        for (int j = i; j < input.size(); j++) {
            sum += input[j];
            max = std::max(sum, max);
        }
    }
    return max;
}
            
void test() {
    int len = 100;
    std::vector<int> input = rnd_intvec(len);
    print(input.begin(), input.end());
    std::cout<<"Accumulate: "<<std::accumulate(input.begin(), input.end(), 0L)<<std::endl;
    std::cout<<"Int max: "<<std::numeric_limits<int>::max()<<std::endl;
    std::cout<<max_sum_subarray(input)<<" "<<bruteforce(input)<<std::endl;
}

int main() {
    test();
}
    

