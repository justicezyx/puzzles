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
    vector<vector<int> > levelOrder(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> res;
        if (root == NULL) {
            return res;
        }
        vector<TreeNode*> cur_level(1, root);
        while (!cur_level.empty()) {
            vector<int> tmp;
            tmp.reserve(cur_level.size());
            vector<TreeNode*> next_level;
            next_level.reserve(cur_level.size() * 2);
            for (int i = 0; i < cur_level.size(); ++i) {
                tmp.push_back(cur_level[i]->val);
                if (cur_level[i]->left) {
                    next_level.push_back(cur_level[i]->left);
                }
                if (cur_level[i]->right) {
                    next_level.push_back(cur_level[i]->right);
                }
            }
            res.push_back(tmp);
            cur_level = next_level;
        }
        return res;
    }
};
