#include "common.h"

/**
 * Find the maximum rectangle inside the area of a histogram.
 * The width of each histogram is assumed to be 1.
 */
int max_rectangle_histogram(const std::vector<int>& histogram) {
    if (histogram.size() == 0) {
        return 0;
    }

    if (histogram.size() == 1) {
        return histogram[0];
    }

    std::stack<std::pair<int,int> > h;
    h.push(std::make_pair(histogram[0], 0));

    // initially max is the size of the first bar.
    int max = 0;
    for ( int i = 1; i < histogram.size(); ++i) {
        int lb = i;
        while (!h.empty() && h.top().first > histogram[i]) {
            std::cout<<"poping"<<std::endl;
            int top_size = h.top().first * (i - h.top().second);
            max = std::max(max, top_size);
            lb = h.top().second;
            h.pop();
        }   

        // Do not push if the top element is same height as the current one.
        if (h.empty() || h.top().first < histogram[i]) {
            h.push(std::make_pair(histogram[i], lb));
        }
    }   
    
    std::cout<<h.top().first<<" "<<h.top().second<<std::endl;
    while (!h.empty()) {
        int top_size = h.top().first * (histogram.size() - h.top().second);
        max = std::max(max, top_size);
        h.pop();
    }   
    return max;
}

void test() {
    int A[] = {0, 1, 1, 1, 1};
    std::vector<int> input(A, A + sizeof(A) / sizeof(int));
    std::cout<<max_rectangle_histogram(input)<<std::endl;
}

int main() {
    test();
}
