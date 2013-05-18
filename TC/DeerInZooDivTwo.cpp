#include "../common.h"

pair<int, int> solution(int n, int k) {
    int min = std::max(0, n - k);
    int max = n - (k/2 + k%2);
    return make_pair(min, max);
}

int main() {
    pair<int, int> res = solution(3, 2);
    cout<<res.first<<" "<<res.second<<endl;

    res = solution(3, 3);
    cout<<res.first<<" "<<res.second<<endl;

    res = solution(654, 321);
    cout<<res.first<<" "<<res.second<<endl;
}
