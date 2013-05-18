#include <iostream>
#include <vector>
#include <algorithm>

#include "common.h"

int longest_incseq(const std::vector<int>& num) {
    std::vector<int> end_idx_for_incseq_len(num.size() + 1, -1);
    std::vector<int> end_val_for_incseq_len(num.size() + 1);
    std::vector<int> prev(num.size(), -1);

    end_idx_for_incseq_len[1] = 0;
    end_val_for_incseq_len[1] = num[0];
    prev[0] = -1;

    int max = 1;
    typedef std::vector<int>::iterator itor;
    for (int i = 1; i < num.size(); i++) {
        itor begin = end_val_for_incseq_len.begin() + 1;
        itor end = begin + max;
        itor pos = std::upper_bound(begin, end, num[i]);
        if (pos == begin) {
            *pos = num[i];
            end_idx_for_incseq_len[1] = i;
            end_val_for_incseq_len[1] = num[i];
        } else if (*(pos - 1) < num[i]) {
            int updated_len = pos - begin + 1;
            end_idx_for_incseq_len[updated_len] = i;
            *pos = num[i];
            prev[i] = end_idx_for_incseq_len[updated_len - 1];

            if (pos == end) { ++max; }
        }
    }
    
    int right_idx = end_idx_for_incseq_len[max];
    while (right_idx != -1) {
        std::cout<<num[right_idx]<<" ";
        right_idx = prev[right_idx];
    }
    std::cout<<std::endl;

    return max;
}

void test() {
    srand(time(0));

    int size = 20;
    std::vector<int> input;
    input.reserve(size);
    for (int i = 0; i < input.capacity(); i++) {
        input.push_back(rand() % 20);
    }

    std::cout<<"Input: "<<std::endl;
    print(input.begin(), input.end());
    std::cout<<longest_incseq(input)<<std::endl;
}

int main() {
    test();
}
