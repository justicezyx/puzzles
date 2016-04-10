#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>

struct compareable_interval {
    int start;
    int end;
    int real_start;
    int real_end;
    
    compareable_interval(int lhs, int rhs) : start(lhs), end(rhs),
                                             real_start(lhs), real_end(rhs) { }

    compareable_interval(int l, int r, int rl, int rr) : start(l), end(r),
                                                         real_start(rl), real_end(rr) { }

    bool inside(int val) const {
        return val >= start && val <= end;
    }

    int realValue(int val) const {
        return real_start + val - start;
    }
    
    bool operator<(const compareable_interval& other) const {
        return end < other.start;
    }

    bool operator==(const compareable_interval& other) const {
        return inside(other.start) && inside(other.end);
    }

    friend std::ostream& operator<<(std::ostream& out, 
                                    const compareable_interval& other) {
        out<<other.start<<" "<<other.end;
        return out;
    }
};

std::vector<compareable_interval> compile(const std::vector<int>& nums, int n) {
    std::vector<compareable_interval> res;
    int prev_start = nums.front();
    int prev = nums.front();
    if (prev > 0) {
        compareable_interval interval(0, prev_start - 1, 0, prev_start - 1);
        res.push_back(interval);
    }

    typedef std::vector<int>::const_iterator itor;
    itor idx = nums.begin();

    for (++idx; idx != nums.end(); ++idx) {
        int cur = *idx;
        if (cur != prev + 1) {
            int len = cur - prev - 1;
            compareable_interval interval(prev_start, prev_start + len - 1, prev + 1, cur - 1);
            res.push_back(interval);
            prev = cur;
            prev_start = prev_start + len;
        } else {
            prev = cur;
        }
    }

    int len = n - prev - 1;
    if (len > 0) {
        compareable_interval interval_last(prev_start, prev_start + len - 1, prev + 1, n - 1);
        res.push_back(interval_last);
    }
    return res;
}

int rand(int n, const std::vector<int>& except) {
    std::vector<compareable_interval> candidate = compile(except, n);
    int m = n - except.size();
    
    int val = rand() % m;
    typedef std::vector<compareable_interval>::iterator itor;
    compareable_interval interval(val, val);
    itor found = std::lower_bound(candidate.begin(), candidate.end(), interval);
    return found->realValue(val);
}

int main() {
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(9);

    std::vector<compareable_interval> res = compile(nums, 10);
    std::copy(res.begin(), res.end(), std::ostream_iterator<compareable_interval>(std::cout, "\n"));
    
    srand(time(0));
    std::cout<<rand(10, nums)<<std::endl;
}
