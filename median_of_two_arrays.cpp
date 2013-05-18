double findKth(int a[], int m, int b[], int n, int k)
{
    if (m > n) return findKth(b, n, a, m, k);

    if (m == 0) return b[k-1];
    if (k == 1) return min(a[0], b[0]);
    int pa = min(k/2, m), pb = k - pa;
    if (a[pa-1] < b[pb-1]) return findKth(a+pa, m-pa, b, n, k - pa);
    return findKth(a, m, b+pb, n-pb, k-pb);
}

class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int total = m+n;
        if(total&0x1) {
            return findKth(A, m, B, n, total/2+1);
        } else {
            return (findKth(A, m, B, n, total/2) + findKth(A, m, B, n, total/2+1))/2;
        }
    }
};
