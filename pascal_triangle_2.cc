class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        std::vector<int> res(rowIndex + 1, 1);
        for (int i = 0; i < rowIndex + 1; ++i) {
            for (int j = 1, l = 1; j <= i; ++j) {
                int right = j;
                if (right >= i) {
                    res[j] = 1;
                } else {
                    int t = res[j];
                    res[j] = l + res[right];
                    l = t;
                }
            }
        }
        return res;
    }
};
