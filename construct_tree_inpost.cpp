#include "common.h"

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int data;
    TreeNode(int val) : data(val), left(NULL), right(NULL) { }
};

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
    TreeNode *buildTree(std::vector<int> &inorder, std::vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        // from the postorder's last node to find the root of current sub tree
        // Split the in order into 2 parts, first for left sub tree, and right for right subtree, corresponding to the first part and the second part of postorder.
        return build(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }

    TreeNode* build(const std::vector<int>& inorder, int in_b, int in_e, const std::vector<int>& postorder, int post_b, int post_e) {
        std::cout<<in_b<<" "<<in_e<<" "<<post_b<<" "<<post_e<<std::endl;

        if (in_e - in_b == 1) { return new TreeNode(inorder[in_b]); }
        if (in_e - in_b <= 0) { return NULL; }
        
        int root_val = postorder[post_e - 1];
        int i = in_b;
        for (; i < in_e && inorder[i] != root_val; ++i);

        TreeNode* left = build(inorder, in_b, i, postorder, post_b, post_b + i - in_b);
        TreeNode* right = build(inorder, i + 1, in_e, postorder, post_b + i - in_b, post_e - 1);
        TreeNode* root = new TreeNode(root_val);
        root->left = left;
        root->right = right;
        return root;
    }
};

void test() {
    int IN[] = {2, 1, 3};
    int POST[] = {2, 3, 1};

    std::vector<int> inorder(IN, IN + sizeof(IN) / sizeof(int));
    std::vector<int> postorder(POST, POST + sizeof(POST) / sizeof(int));
    
    Solution solution;
    TreeNode* root = solution.buildTree(inorder, postorder);
}

int main() {
    test();
}
