/**
 * Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
 *
 * You may assume that the intervals were initially sorted according to their start times.
 *
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 *
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
 *
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 */

#include "common.h"
using namespace std;

struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
};

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

bool pos_comp(const Interval& lhs, const Interval& rhs) {
    return lhs.end < rhs.start;
}

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        typedef vector<Interval>::iterator itor_t;
        pair<itor_t,itor_t> itor_pair = equal_range(intervals.begin(), intervals.end(), newInterval, pos_comp);
        int new_start = newInterval.start;
        if (itor_pair.first != intervals.end()) {
            new_start = std::min(new_start, itor_pair.first->start);
        }
        
        int new_end = newInterval.end;
        if (itor_pair.second != intervals.begin()) {
            new_end = std::max(new_end, (itor_pair.second-1)->end);
        }
        
        Interval to_be_inserted(new_start, new_end);
        
        vector<Interval> res;
        res.insert(res.end(), intervals.begin(), itor_pair.first);
        res.push_back(to_be_inserted);
        res.insert(res.end(), itor_pair.second, intervals.end());
        return res;
    }
};

int main() {
    Interval interval(1, 5);
    vector<Interval> intervals;
    intervals.push_back(interval);

    Interval iint(2, 7);
    insert(intervals, iint);
}
