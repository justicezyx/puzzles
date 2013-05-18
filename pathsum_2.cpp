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
    std::vector<std::vector<int>> res;
public:
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        res.clear();
        if (root == NULL) {
            return res;
        }
        
        std::vector<int> path;
        path.push_back(root->val);
        post_order(root, path, root->val, sum);
        return res;
    }
    
    void post_order(TreeNode* root, std::vector<int>& path, int partial_sum, int sum) {
        if (partial_sum == sum && root->left == NULL & root->right == NULL) {
            res.push_back(path);
            return;
        }
        
        if (root->left != NULL) {
            partial_sum += root->left->val;
            path.push_back(root->left->val);
            post_order(root->left, path, partial_sum, sum);
            path.pop_back();
            partial_sum -= root->left->val;
        }
        
        if (root->right != NULL) {
            partial_sum += root->right->val;
            path.push_back(root->right->val);
            post_order(root->right, path, partial_sum, sum);
            path.pop_back();
            partial_sum -= root->right->val;
        }
    }
};
