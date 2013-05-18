#include "common.h"

/**
 * Given a list of integers, and another integeri 'v'.
 * Find a sub set of the list that sum up eaquals to the integer, and has the maximum number of elements.
 * 
 * Solution:
 * 1. srot the list.
 * 2. define a subroutine, which enumerate a subset of the list that has a fixed size of 'n', in ascending order.
 *    Perform a binary search on the size 'n'.
 * 3. Find the largest 'i', such that sum[0,...,i] <= v and sum[0,...,i+1] > v; denote this value as 'm'.
 * 4. It's obvious that the size of the subset is in [1, m], search from 'm' to '1' using the subroutine
 *
 * the subroutine will maintain two lists of numbers, the first is the partial results, which has 'n' elements.
 * the other is a list of elements that has not been put into the first list. Each time we are trying to increase
 * the first list as smaller as possible. Until it is equal to 'v', then we can return; or go to next size.
 */

int next(const std::vector<int>& num, std::vector<int>& partial, std::vector<int>& candidate) {
    // num is a sorted array.
    // partial are the selected indices in num
    // candidate are the available indices in num
    if (candidate.back() < partial.front()) {
        // The largest candidate is less than the smallest in partial, cann be larger.
        return 0;
    }
    
    int min_i;
    int min_sub;
    int min_incremental = std::numeric_limits<int>::max();
    for (int i = 0; i < partial.size(); ++i) {
        int cur = num[partial[i]];
        int sub = -1;
        int j = 0;
        while (j < candidate.size()) {
            if (num[candidate[j]] > cur) {
                sub = j;
                break;
            }
            ++j;
        }
        int inc = num[candidate[sub]] - cur;
        if (inc < min_incremental) {
            min_i = i;
            min_sub = sub;
            min_incremental = inc;
        }
    }
    std::swap(partial[min_i], candidate[min_sub]);
    return min_incremental;
}
        
std::pair<int,int> maxlen(const std::vector<int>& num, int max) {
    int res = 0;
    int sum = 0;
    for (; res < num.size() && sum < max; ++res) {
        sum += num[res];
    }
    // return the sum and length.
    return std::make_pair(res, sum);
}

std::vector<int> search(const std::vector<int>& num, int v) {
    std::pair<int,int> t = maxlen(num, v);
    int len = t.first;
    int sum_len = t.second;
    std::vector<int> res;
    std::vector<int> rest;
    res.reserve(len);
    rest.reserve(num.size() - len);
    for (int i = 0; i < len; ++i) {
        res.push_back(i);
    }
    for (int i = len; i < num.size(); ++i) {
        rest.push_back(i);
    }

    if (sum_len == v) {
        return res;
    }
    if (len >= num.size()) {
        return std::vector<int>();
    }

    for (; len >= 1; sum_len -= num[len-1], --len) {
        std::vector<int> partial = res;
        //std::cout<<"partial:"; print(partial.begin(), partial.end());
        //std::cout<<"\nsum:"<<sum_len<<std::endl;

        std::vector<int> candidate = rest;
        //std::cout<<"rest:"; print(rest.begin(), rest.end());
        //std::cout<<std::endl;

        int partial_sum = sum_len;
        for (;;) {
            int inc = next(num, partial, candidate);
            if (inc == 0) {
                return std::vector<int>();
            }
            partial_sum += inc;
            if (partial_sum == v) {
                return partial;
            }
            if (partial_sum > v) {
                break;
            }
        }
        int back = res.back();
        res.pop_back();
        rest.insert(rest.begin(), back);
    }
    return std::vector<int>();
}

int rnd_10() {
    return rand() % 10 + 1;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    std::vector<int> num = rnd_fill(20, rnd_10);
    std::sort(num.begin(), num.end());
    print(num.begin(), num.end());

    std::cout<<"start"<<std::endl;
    std::vector<int> res = search(num, atoi(argv[1]));
    for (int i = 0; i < res.size(); ++i) {
        std::cout<<num[res[i]]<<(i == res.size() - 1 ? "\n" : " ");
    }
}
