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
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL) {
            return false;
        }
        
        return path_sum(root, sum);
    }
    
    bool path_sum(TreeNode *root, int sum) {
        if (root->left == NULL && root->right == NULL) {
            if (root->val == sum) return true;
            else return false;
        }
        
        if (root->left != NULL && path_sum(root->left, sum - root->val))
            return true;
        if (root->right != NULL && path_sum(root->right, sum - root->val))
            return true;
        return false;
    }
};
