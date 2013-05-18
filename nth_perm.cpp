class Solution {
public:
    string getPermutation(int n, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> fac;
        fac.resize(n + 1, 0);
        fac[1] = 0;
        fac[2] = 1;
        for (int i = 3; i <= n; ++i) {
            fac[i] = (i-1) * fac[i-1];
        }
        
        vector<int> perm;
        perm.reserve(n);
        for (int i = 1; i <= n; ++i) {
            perm.push_back(i);
        }
        
        if (k == 1) {
            ostringstream oss;
            for (int i = 0; i < n; ++i) {
                oss << perm[i];
            }
            return oss.str();
        }
        
        for (int i = n, j = 0; i >= 0 && k > 1; --i, ++j) {
            if (k > fac[i]) { 
                int inv = (k-1) / fac[i];
                sort(perm.begin() + j, perm.end());
                swap(perm[j], perm[j+inv]);
                sort(perm.begin() + j + 1, perm.end());
                k = k - inv * fac[i];
            }
        }
        
        ostringstream oss;
        for (int i = 0; i < n; ++i) {
            oss<<perm[i];
        }
        return oss.str();
    }
};
