/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return balance_height(root) != -1;
    }
    
    int balance_height(TreeNode* root) {
        // return -1 if its not balanced.
        if (root == NULL) { return 0; }
        int l = balance_height(root->left);
        int r = balance_height(root->right);
        if (l == -1 || r == -1) {
            return -1;
        }
        if (abs(l-r) > 1) {
            return -1;
        }
        return std::max(l, r) + 1;
    }
};
