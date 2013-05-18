/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
bool compare(const Interval& lhs, const Interval& rhs) {
    return lhs.start < rhs.start;
}

class Solution {
public:

    vector<Interval> merge(vector<Interval> &intervals) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<Interval> res;
        if (intervals.empty()) { return res; }
        
        sort(intervals.begin(), intervals.end(), compare);
        
        // sort(intervals.begin(), intervals.end(), compare);
        for (int i = 0; i < intervals.size(); ) {
            long cur_begin = intervals[i].start;
            long cur_end = intervals[i].end;
            int j = i + 1;
            while (j < intervals.size() && intervals[j].start <= cur_end) {
                int tmp = intervals[j].end;
                if (tmp > cur_end) { cur_end = tmp; }
                ++j;
            }
            res.push_back(Interval(cur_begin, cur_end));
            i = j;
        }
        return res;
    }
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

bool compare(const Interval& lhs, const Interval& rhs) {
    return lhs.start < rhs.start;
}

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(intervals.begin(), intervals.end(), compare);
        
        vector<Interval> res;
        res.reserve(intervals.size());
        
        for (int i = 0; i < intervals.size(); ) {
            int begin = intervals[i].start;
            int end = intervals[i].end;
            
            int j = i + 1;
            while (j < intervals.size() && intervals[j].start <= end) {
                end = max(end, intervals[j].end);
                ++j;
            }
            res.push_back(Interval(begin,end));
            i = j;
        }
        return res;
    }
};
