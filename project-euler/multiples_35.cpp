#include "../common.h"
using namespace std;

int main() {
    int res = 0;
    for (int b = 3, i = 1, v = 3; v < 1000; ++i, v = i * b) {
        res += v;
        cout<<v<<" "<<i<<endl;
    }
    for (int b = 5, i = 1, v = 5; v < 1000; ++i, v = i * b) {
        if (v % 3 != 0) {
            cout<<v<<endl;
            res += v;
        }
    }
    cout<<res<<endl;
    return res;
}
