#include "common/common.h"
using namespace std;

int rand_m(int max, int m, int n) {
    // m-n < max
    // m = 1, n = 2;
    int new_range = m-n+1; // 11 - 5 + 1 = 7; new_range == 2;
    int original_range = max+1; // max == 32001
    if (new_range > original_range) {
        // invalid input
    }
    
    int max_k = original_range / new_range; //max_k == 1; max_k == 16000
    int V = max_k * new_range; // V == 7, V == 32000
    cout<<"V:"<<V<<endl;
    cout<<"max_k:"<<max_k<<endl;
    while (true) {
        int tmp = rand(); // which is less than 7; asume tmp = 1
        if (tmp < V) { // 1 < 7, return 1 / max_k + m, return 6
            return tmp / max_k + m; // divide by 32000, return, for any value < 16000, return 1, for [16000, 32000)
        }
    }
}

int main() {
    cout<<rand_m(10, 1, 0)<<endl;
}
