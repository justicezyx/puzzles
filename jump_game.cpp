#include "common.h"

int jump_opt(const std::vector<int>& A) {
    int step = 0;
    int cur = 0;
    int next = 0;
    
    for (int i = 0; i < A.size() && next < A.size() - 1; ++i) {
        std::cout<<"Iteration:"<<i<<std::endl;
        if (i > cur && i <= next) {
            // current position is out of current reachable distance.
            // and is in the reachable distance with 1 more step.
            ++step;
            cur = next;
        } else if (i > next) {
            // impossible to go forward.
            return -1;
        }
        next = std::max(next, i + A[i]);
    }

    if (cur < A.size() - 1) {
        return step + 1;
    } else {
        return step;
    }
}
int jump(const std::vector<int>& A) {
    int step = 0;
    int cur = 0;
    int next = 0;
    
    for (int i = 0; i < A.size(); ++i) {
        std::cout<<"Iteration:"<<i<<std::endl;
        if (i > cur && i <= next) {
            // current position is out of current reachable distance.
            // and is in the reachable distance with 1 more step.
            ++step;
            cur = next;
        } else if (i > next) {
            // impossible to go forward.
            return -1;
        }
        next = std::max(next, i + A[i]);
    }

    return step;
}

void test() {
    int a[] = {100, 0, 1, 1, 1};
    std::vector<int> input(a, a + 5);
    std::cout<<jump(input)<<std::endl;
}

int main() {
    test();
}
