
/**
 * Given a tree, each node has a digit in [0, 9]; the path from root to leaf
 * presents a positional-notation number. Sum all such numbers in a tree.
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
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) { return 0; }
        int sum = 0;
        post_order(root, 0, sum);
        return sum;
    }
    
    void post_order(TreeNode* root, int val, int& sum) {
        val = val * 10 + root->val;
        
        if (root->left == NULL && root->right == NULL) {
            sum += val;
        }
        
        if (root->left) {
            post_order(root->left, val, sum);
        }
        
        if (root->right) {
            post_order(root->right, val, sum);
        }
    }
};
