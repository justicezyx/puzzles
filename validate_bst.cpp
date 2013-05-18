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
    bool isValidBST(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        long long lower_bound = static_cast<long long>(numeric_limits<int>::min()) - 1;
        long long upper_bound = static_cast<long long>(numeric_limits<int>::max()) + 1;
        return validate(root, lower_bound, upper_bound);
    }
    
    bool validate(TreeNode* root, long long lower_bound, long long upper_bound) {
        if (root == NULL) {
            return true;
        }
        if (root->val <= lower_bound || root->val >= upper_bound) {
            return false;
        }
        return validate(root->left, lower_bound, root->val) 
            && validate(root->right, root->val, upper_bound);
    }
};
