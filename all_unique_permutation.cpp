#include "common.h"

void helper(std::vector<int>& num, int begin, int end, std::vector<std::vector<int> >& res) {
    std::cout<<"candidate:";
    print(num.begin() + begin, num.begin() + end);
    if (end - begin == 1) {
        print(num.begin(), num.end());
        res.push_back(num);
        return;
    }
    
    for (int i = begin; i < end; ++i) {
        if (i != begin && num[i] == num[begin]) { continue; }
        if (i != begin && num[i] == num[i-1]) { continue; }

        std::swap(num[begin], num[i]);
        helper(num, begin + 1, end, res);
        std::swap(num[begin], num[i]);
    }
}

std::vector<std::vector<int> > permute(std::vector<int> &num) {
    std::vector<std::vector<int> > res;
    if (num.empty()) {
        return res;
    }
    do {
        res.push_back(num);
    } while (std::next_permutation(num.begin(), num.end()));
    return res;
}

void test() {
    int A[] = {1,1,1,2,2,3,3,4};
    std::sort(A, A + sizeof(A) / sizeof(int));
    std::vector<int> res(A, A + sizeof(A) / sizeof(int));
    std::cout<<"result size: "<<permute(res).size()<<std::endl;
}

int main() {
    test();
}
