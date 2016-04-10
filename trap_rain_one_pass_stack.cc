class Solution {
public:
    int trap(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<pair<int,int>> h;
        for (int i = 0; i < n; ++i) {
            int partial = 0;
            while (!h.empty() && A[i] >= A[h.top().first]) {
                int tmp = h.top().second;
                int height = A[h.top().first];
                h.pop();
                partial += tmp;
                if (!h.empty()) {
                    partial += (i - h.top().first-1) * (min(A[i], A[h.top().first]) - height);
                }
            }
            h.push(make_pair(i, partial));
        }
        int res = 0;
        while (!h.empty()) {
            res += h.top().second;
            h.pop();
        }
        return res;
    }
};
