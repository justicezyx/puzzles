#include "common.h"

typedef std::pair<int,int> interval_t;
typedef std::list<interval_t> interval_list_t;

void insert(interval_list_t& interval_list, interval_t interval) {
    typedef interval_list_t::iterator iterator;
    std::vector<int> h;
    h.reserve(2 * interval_list.size());
    for (iterator i = interval_list.begin(); i != interval_list.end(); ++i) {
        h.push_back(i->first);
        h.push_back(i->second);
    }

    typedef std::vector<int>::iterator vec_iterator;
    vec_iterator left = std::lower_bound(h.begin(), h.end(), interval.first);
    vec_iterator right = std::upper_bound(h.begin(), h.end(), interval.second);

    h.erase(left, right);
    int left_dist = std::distance(h.begin(), left);
    int right_dist = std::distance(h.begin(), right);
    std::cout<<"left distance: "<<left_dist<<" right distance: "<<right_dist<<std::endl;
    if (left_dist % 2 == 0 && right_dist % 2 == 0) {
        // This also applies to the case where the right end is 1 pass the array.
        // left is the beginning of an interval.
        // right is the begin of an interval.
        std::cout<<"left: "<<left_dist<<" right: "<<right_dist<<std::endl;
        vec_iterator tmp = h.insert(left, interval.second);
        h.insert(tmp, interval.first);
    } else if (left_dist % 2 == 0 && right_dist % 2 != 0) {
        // left is begin, right is end
        h.insert(left, interval.first);
    } else if (left_dist % 2 != 0 && right_dist % 2 == 0) {
        // left is end of an interval, the right is bein of an interval.
        h.insert(left, interval.second);
    }         

    interval_list_t res;
    for (int i = 0; i < h.size(); i += 2) {
        res.push_back(std::make_pair(h[i], h[i+1]));
    }

    interval_list = res;
}

template<typename First, typename Second>
std::ostream& operator<<(std::ostream& os, const std::pair<First,Second>& v) {
    os<<"["<<v.first<<","<<v.second<<"]";
    return os;
}

void test() {
    interval_list_t input;

    input.push_back(std::make_pair(1, 3));
    input.push_back(std::make_pair(5, 7));
    input.push_back(std::make_pair(9, 10));

    insert(input, std::make_pair(11, 12));

    typedef interval_list_t::iterator itor;
    for (itor i = input.begin(); i != input.end(); ++i) {
        std::cout<<*i<<std::endl;
    }
}

int main() {
    test();
}
