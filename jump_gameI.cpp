#include "common.h"

/**
 * Given an integer array, it gives the max dist can jump
 * from the current position. Determine if the last position 
 * is reachable from the first one.
 */
bool is_reachable(const std::vector<int>& A) {
    int max = 0;
    int max_pos = A.size() - 1;
    for (int i = 0; max < max_pos && i <= max && i <= max_pos; ++i) {
        max = std::max(max, i + A[i]);
    }
    return max >= max_pos;
}
        
void test() {
    int A[] = {3,2,1,0,4};
    std::vector<int> input(A, A + 5);
    std::cout<<is_reachable(input);
}

int main() {
    test();
}
