#include "common.h"

/**
 * Given an input array and a value, find the subarray that sums up equals to the value,
 * and has the maximum length.
 */
std::pair<int,int> longest_subarray_sum(const std::vector<int>& array, int sum) {
    if (array.size() == 0) {
        return std::make_pair(0, 0);
    }

    if (array.size() == 1) {
        return std::make_pair(0, array[0] == sum ? 1 : 0);
    }

    // stores the mapping between <prefix sum> : <idx of the right most index>
    std::map<int,int> prefix_sum_map;
    typedef std::map<int,int>::iterator itor;

    int prefix_sum = 0;
    int left = 0;
    int right = 0;
    for (int i = 0; i < array.size(); ++i) {
        // accumulate prefix sum.
        prefix_sum += array[i];

        // get the window's left end that sums up equals to sum.
        itor tmp = prefix_sum_map.find(prefix_sum - sum);
        if (tmp != prefix_sum_map.end()) {
            // has a previous value defined.
            if (i - tmp->second > right - left) {
                left = tmp->second + 1;
                right = i + 1;
            }
        }

        tmp = prefix_sum_map.find(prefix_sum);
        if (tmp == prefix_sum_map.end()) {
            prefix_sum_map[prefix_sum] = i;
        }
    }
    return std::make_pair(left, right);
}

int rand_10() {
    return rand() % 10 + 1;
}

void test() {
    std::vector<int> array = rnd_fill(100, rand_10);
    print(array.begin(), array.end());
    std::cout<<std::endl;
    
    std::pair<int,int> res = longest_subarray_sum(array, 10);
    std::cout<<res.first<<" "<<res.second<<std::endl;
}

int main() {
    test();
}
