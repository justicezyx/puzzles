#include "common.h"
using namespace std;

int uniquePaths(int m, int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (m > n) {
        swap(m, n);
    }
    double res = 1.0;
    for (int i = 1; i <= m; --i) {
        res = res * (m+n-i+1) / i;
    }
    return (int)res;
}

int main() {
    std::cout<<uniquePaths(1, 2);
}
