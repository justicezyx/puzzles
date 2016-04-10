/**
 * Find the all permutations of the elements of an input array.
 */
class Solution {
public:
    vector<vector<int>> permute(vector<int> &num) {
        if (num.size() == 0) {
            return std::vector<std::vector<int>>();
        }
        if (num.size() == 1) {
            return std::vector<std::vector<int>>(1, std::vector<int>(1, num[0]));
        }
        
        std::vector<std::vector<int>> res;
        for (int i = 0; i < num.size(); ++i) {
            std::swap(num[0], num[i]);
            std::vector<int> sub = std::vector<int>(num.begin() + 1, num.end());
            std::vector<std::vector<int>> partial = permute(sub);
            for (int i = 0; i < partial.size(); ++i) {
                partial[i].push_back(num[0]);
            }
            res.insert(res.end(), partial.begin(), partial.end());
        }
        return res;
    }
};
