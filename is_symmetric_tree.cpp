/*
 * Symmetric TreeSep 24 '121096 / 2190
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
 *
 * For example, this binary tree is symmetric:
 *
 *     1
 *        / \
 *          2   2
 *           / \ / \
 *           3  4 4  3
 *           But the following is not:
 *
 *               1
 *                  / \
 */

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
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }
    
        return helper(root, root);
    }

    bool helper(TreeNode* lhs, TreeNode* rhs) {
        if (lhs == NULL && rhs == NULL) {
            return true;
        }
        if (lhs == NULL || rhs == NULL) {
            return false;
        }
        if (lhs->val != rhs->val) {
            return false;
        }
        return helper(lhs->left, rhs->right) 
            && helper(lhs->right, rhs->left);
    }
};
