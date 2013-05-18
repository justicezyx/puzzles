#include <iostream>
#include <stack>

int helper(int* h, int l) {
    if (l <= 2) { return 0; }
    if (l == 3) {
        return std::max(0, std::min(h[0], h[2]) - h[1]);
    }
}

int find_max(int* h, int l) {
    if (l <= 0) { return -1; }
    
    int max = h[0];
    int maxi = 0;
    for (int i = 1; i < l; i++) {
        if (h[i] > max) {
            max = h[i];
            maxi = i;
        }
    }
    return maxi;
}

int reservior_twopass(int* h, int l) {
    if (l <= 3) {
        return helper(h, l);
    }

    int maxi = find_max(h, l);
    
    int max = 0;
    int begin = h[0];
    
    for (int i = 1; i < maxi; i++) {
        max += std::max(0, begin - h[i]);
        begin = std::max(begin, h[i]);
    }

    begin = h[l - 1];

    for (int i = l - 2; i > maxi; i--) {
        max += std::max(0, begin - h[i]);
        begin = std::max(begin, h[i]);
    }

    return max;
}

struct node {
    int h;
    int i;
    int v;
    node(int height, int idx, int val) {
        h = height;
        i = idx;
        v = val;
    }
};

int reservior_onepass(int *h, int l) {
    if (l <= 3) {
        return helper(h, l);
    }

    std::stack<node> s;
    s.push(node(h[0], 0, 0));
    
    for (int i = 1; i < l; i++) {
        int cur_max = 0;
        while (!s.empty() && s.top().h < h[i]) {
            // need to pop.
            node t = s.top();
            s.pop();
            cur_max += t.v; // stored area.

            if (!s.empty()) {
                cur_max += (i - s.top().i - 1) * (std::min(h[i], s.top().h) - t.h); // poped area.
            }
        }
        s.push(node(h[i], i, cur_max));
    }
    
    int max = 0;
    while (!s.empty()) {
        max += s.top().v;
        s.pop();
    }

    return max;
}

void test(int l, int maxh) {
    int* h = new int[l];
    for (int i = 0; i < l; i++) {
        h[i] = rand() % maxh;
    }
    std::cout<<reservior_twopass(h, l)<<" "<<reservior_onepass(h, l)<<std::endl;
}

int main() {
    srand(time(0));
    for (int i = 10; i <= 100; i++) {
        test(i, i);
    }
}

