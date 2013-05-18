/**
 * Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.
 *
 * For example:noh
 * Given n = 3, your program should return all 5 unique BST's shown below.
 *
 *    1         3     3      2      1
 *        \       /     /      / \      \
 *           
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
    vector<TreeNode *> generateTrees(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return permute_tree(1, n);
    }
    
    vector<TreeNode*> permute_tree(int begin, int end) {
        if (begin > end) {
            return vector<TreeNode*>(1, (TreeNode*)NULL);
        }
        vector<TreeNode*> res;
        for (int i = begin; i <= end; ++i) {
            typedef vector<TreeNode*>::iterator itor_t;
            
            vector<TreeNode*> left_roots = permute_tree(begin, i-1);
            vector<TreeNode*> right_roots = permute_tree(i+1, end);
            for (itor_t j = left_roots.begin(); j != left_roots.end(); ++j) {
                for (itor_t k = right_roots.begin(); k != right_roots.end(); ++k) {
                    TreeNode* root = new TreeNode(i);
                    root->left = *j;
                    root->right = *k;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
