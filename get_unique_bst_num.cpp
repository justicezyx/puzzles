/**
 * Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
 */
class Solution {
public:
    int numTrees(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return get_bst_num(1, n);
    }
    int get_bst_num(int begin, int end) {
        if (begin > end) {
            return 1;
        }
        int res = 0;
        for (int i = begin; i <= end; ++i) {
            int left_sub_trees = get_bst_num(begin, i-1);
            int right_sub_trees = get_bst_num(i+1, end);
            res += left_sub_trees * right_sub_trees;
        }
        return res;
    }
};
