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
    vector<int> inorderTraversal(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        std::vector<int> res;
        if (root == NULL) {
            return res;
        }
        
        stack<TreeNode*> h;
        TreeNode* cur = root;
        while (cur) {
            h.push(cur);
            cur = cur->left;
        }
    
        while (!h.empty()) {
            cur = h.top();
            h.pop();
            res.push_back(cur->val);
            
            TreeNode* tmp = cur->right;
            while (tmp) {
                h.push(tmp);
                tmp = tmp->left;
            }
        }
        return res;
    }
};
