#include "common/common.h"
using namespace std;

/**
 * Given an integer array A, find the max(j - i), such that A[j] > A{i].
 */

/**
 * This gives a solution given by this post:
 * (1) build an array M[1...n] with M[i] as the maximum number from A[i] to A[n].
 * For example, for array [1, 9, 2, 8, 3, 7, 4, 6, 5] , the array M would be [9, 9, 8, 8, 7, 7, 6, 6, 5]
 *
 * (2) use two indices, i for array A, and j for array M: initialize i = 0 & j = 0
 *
 * (3) sliding:
 * fixing i, move j forward until A[i] > M[j + 1] or j=n, record the current span j – i
 * fixing j, move i forward until A[i] < M[j + 1]
 * continue spliding i & j until j goes to n.
 */

vector<int> build_min_prefix(const vector<int>& A) {
    vector<int> res(A.size());
    int min = numeric_limits<int>::max();
    for (int i = 0; i < A.size(); ++i) {
        min = std::min(min, A[i]);
        res[i] = min;
    }
    return res;
}

pair<int,int> max_span_backward_solve(const vector<int>& A) {
    int max_span = -1;
    int begin = 0;
    int end = 0;
    vector<int> B = build_min_prefix(A);
    int size = B.size();
    for (int i = size-1, j = size-1; i >= 0 && j >= 0; ) {
        int tmp = A[j];
        while (i >= 0 && B[i] < tmp) {
            --i;
        }
        int span = j - i;
        if (span > max_span) {
            max_span = span;
            begin = i+1;
            end = j;
        }
        
        while (i >= 0 && j >= 0 && A[j] <= B[i]) {
            --j;
        }
    }
    return make_pair(begin, end);
}

vector<int> build_max_suffix(const vector<int>& A) {
    // res gives the max value in A[i:].
    vector<int> res(A.size());
    int max = numeric_limits<int>::min();
    for (int i = A.size()-1; i >= 0; --i) {
        max = std::max(max, A[i]);
        res[i] = max;
    }
    return res;
}

pair<int,int> max_span(const vector<int>& A) {
    int max_span = -1;
    int begin = 0;
    int end = 0;
    vector<int> B = build_max_suffix(A);
    cout<<"max suffix:"<<endl;
    print(B.begin(), B.end());

    for (int i = 0, j = 0; i < A.size() && j+1 < B.size(); ) {
        cout<<"i:"<<i<<" j:"<<j<<endl;
        while (j+1 < B.size() && B[j+1] >= A[i]) {
            ++j;
        }
        int span = j - i;
        if (span > max_span) {
            max_span = span;
            begin = i; end = j;
        }
        
        while (i < A.size() && j+1 < B.size() && A[i] >= B[j+1]) {
            ++i;
        }
    }
    return make_pair(begin, end);
}

int main() {
    int array[] = {1, 9, 2, 8, 3, 7, 4, 6, 5};
    vector<int> A(array, array + sizeof(array)/sizeof(int));
    pair<int,int> res = max_span(A);
    pair<int,int> res2 = max_span_backward_solve(A);
    
    cout<<res.first<<" "<<res.second<<endl;
    cout<<res2.first<<" "<<res2.second<<endl;
}
