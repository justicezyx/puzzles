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
    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return helper(num, 0, num.size());
    }
    
    TreeNode* helper(const std::vector<int>& num, int begin, int end) {
        if (begin >= end) { return NULL; }
        int mid = begin + (end - begin) / 2;
        
        TreeNode* root = new TreeNode(num[mid]);
        TreeNode* left = helper(num, begin, mid);
        TreeNode* right = helper(num, mid + 1, end);
        
        root->left = left;
        root->right = right;
        
        return root;
    }
};
