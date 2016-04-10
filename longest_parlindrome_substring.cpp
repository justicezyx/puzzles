#include "common/common.h"

/**
 * Get the mirrored position of 'r' to the right of center 'c'
 */
int left_mirror(int c, int r) {
    return 2 * c - r;
}

int expand(const std::string& A, int c, int rb) {
    int center_num = 2 * A.size() - 1;
    for (int lb = left_mirror(c, rb); lb >= -1 && rb < center_num; --lb, ++rb) {
        if (lb % 2 == 0 && A[lb/2] != A[rb/2]) {
            break;
        }
    }
    return rb - c - 1;
}

/**
 * Return a list of the start and end position(s) of the
 * longest parlindrom substring of an input string.
 */
std::list<std::pair<int,int> > longest_parlindrome(const std::string& A) {
    std::list<std::pair<int,int> > res;
    res.push_back(std::make_pair(0, 0));

    if (A.size() == 1) {
        return res;
    }

    // The max length of the parlindrome at any possible center position.
    // The center is in [0, 1, 2, 3, ..., 2 * n -1], where all even numbers
    // are for the positions of elements in the string. The odd numbers
    // are for the positions between elements in the string.
    int center_num = 2 * A.size() - 1;
    std::vector<int> h(center_num, 1);
    for (int i = 0; i < A.size() - 2; ++i) {
        h[2 * i + 1] = 0;   // all odd numbers are 0 length.
    }

    int right_most = 1;
    int c = 0;
    int max = 1;

    for (int i = 1; i < center_num; ++i) {
        // i is still in the right most parlindrome.
        // and the mirrored parlindrome does not expand out of the right most one.
        if (left_mirror(c,i) - h[left_mirror(c,i)] > left_mirror(c, right_most)) {
            h[i] = h[left_mirror(c,i)];
        } else {
            h[i] = expand(A, i, right_most + 1);
            if (i + h[i] > right_most) {
                right_most = i + h[i];
                c = i;
            }
        }
                
        int right = (i + h[i]) / 2;
        int left = (i - h[i] + 1) / 2;
        int total_len = right - left + 1;
        if (total_len > max) {
            max = total_len;
            res.clear();
            res.push_back(std::make_pair(left, right));
        } else if (total_len == max && max > 1) {
            res.push_back(std::make_pair(left, right));
        }
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, std::pair<int,int>& v) {
    os<<"["<<v.first<<","<<v.second<<"]";
    return os;
}

int main(int argc, char* argv[]) {
    std::list<std::pair<int,int> > res = longest_parlindrome(std::string(argv[1]));
    typedef std::list<std::pair<int,int> >::iterator itor;
    for (itor i = res.begin(); i != res.end(); ++i) {
        std::cout<<*i<<std::endl;
    }
}
