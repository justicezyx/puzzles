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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> res;
        if (root == NULL) {
            return res;
        }
        
        vector<TreeNode*> cur_level;
        cur_level.push_back(root);
        
        for (int i = 0; !cur_level.empty(); ++i) {
            if (i % 2 == 1) {
                vector<int> tmp;
                tmp.reserve(cur_level.size());
                for (int j = cur_level.size() - 1; j >= 0; --j) {
                    tmp.push_back(cur_level[j]->val);
                }
                res.push_back(tmp);
            } else {
                vector<int> tmp;
                tmp.reserve(cur_level.size());
                for (int j = 0; j < cur_level.size(); ++j) {
                    tmp.push_back(cur_level[j]->val);
                }
                res.push_back(tmp);
            }
            
            vector<TreeNode*> next_level;
            for (int j = 0; j < cur_level.size(); ++j) {
                if (cur_level[j]->left) { 
                    next_level.push_back(cur_level[j]->left);
                }
                if (cur_level[j]->right) { 
                    next_level.push_back(cur_level[j]->right);
                }
            }
            cur_level = next_level;            
        }
        return res;
    }
};
