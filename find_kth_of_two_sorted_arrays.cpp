#include "common.h"
using namespace std;
/*
int find_kth(int k, int A[], int a_len, int B[], int b_len) {
    if (a_len <= 0) {
        return B[k-1];
    }
    if (b_len <= 0) {
        return A[k-1];
    }
    if (k == 1) {
        return min(A[0], B[0]);
    }
    
    int a_advance = min(a_len, k/2);
    int b_advance = min(b_len, k/2);
    if (A[a_advance-1] < B[b_advance-1]) {
        return find_kth(k - a_advance, A+a_advance, a_len - a_advance, B, b_len);
    } else {
        return find_kth(k - b_advance, A, a_len, B+b_advance, b_len - b_advance);
    }
}
*/

int find_kth(int k, int A[], int a_len, int B[], int b_len) {
    if (a_len <= 0) {
        return B[k];
    }
    if (b_len <= 0) {
        return A[k];
    }
    if (k == 0) {
        return min(A[0], B[0]);
    }

    cout<<"k:"<<k<<endl;
    int a_advance = min(a_len, (k+1)/2);
    cout<<"a_advance:"<<a_advance<<" alen:"<<a_len<<endl;
    int b_advance = min(b_len, (k+1)/2);
    cout<<"b_advance:"<<b_advance<<" blen:"<<b_len<<endl;
    if (A[a_advance-1] < B[b_advance-1]) {
        return find_kth(k-a_advance, A+a_advance, a_len-a_advance, B, b_len);
    } else {
        return find_kth(k-b_advance, A, a_len, B+b_advance, b_len-b_advance);
    }
}
int main() {
    int A[] = {2,3,4};
    int B[] = {1};
    int first = find_kth(1, A, 3, B, 1);
    int second = find_kth(2, A, 3, B, 1);
    cout<<first<<" "<<second<<endl;
}
