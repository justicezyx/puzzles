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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        std::vector<std::vector<TreeNode*>> res;
        std::vector<std::vector<int>> val_res;
        if (root == NULL) {
            return val_res;
        }
        std::vector<TreeNode*> cur(1, root);
        res.push_back(cur);
        
        while (!res.back().empty()) {
            std::vector<TreeNode*> next;
            for (int i = 0; i < res.back().size(); ++i) {
                if (res.back()[i]->left) {
                    next.push_back(res.back()[i]->left);
                }
                if (res.back()[i]->right) {
                    next.push_back(res.back()[i]->right);
                }
            }
            res.push_back(next);
        }
        
        res.pop_back();
        
        val_res.reserve(res.size());
        for (auto itor = res.rbegin(); itor != res.rend(); ++itor) {
            std::vector<int> t;
            t.reserve(itor->size());
            for (int i = 0; i < itor->size(); ++i) {
                t.push_back((*itor)[i]->val);
            }
            val_res.push_back(t);
        }
        return val_res;
    }
};
