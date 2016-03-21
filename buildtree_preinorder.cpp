#include "common.h"

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int data;
    TreeNode(int v) {
        data = v;
        left = NULL;
        right = NULL;
    }
};

TreeNode* build_tree_recursive(const std::vector<int>& preorder, int pre_b, int pre_e,
                               const std::vector<int>& inorder, int in_b, int in_e);

TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    return build_tree_recursive(preorder, 0, preorder.size(), inorder, 0, inorder.size());
}

TreeNode* build_tree_recursive(const std::vector<int>& preorder, int pre_b, int pre_e,
                               const std::vector<int>& inorder, int in_b, int in_e) {
    if (pre_e <= pre_b) {
        return NULL;
    }
    if ((pre_e - pre_b) == 1) {
        return new TreeNode(preorder[pre_b]);
    }
    int root_val = preorder[pre_b];
    int root_idx = in_b;
    int dist = 0;
    for (; root_idx < in_e && inorder[root_idx] != root_val; ++root_idx, ++dist);
    std::cout<<"root index:"<<root_idx<<std::endl;

    TreeNode* left = build_tree_recursive(preorder, pre_b+1, pre_b + dist + 1,
                                          inorder, in_b, root_idx);
    TreeNode* right = build_tree_recursive(preorder, pre_b + dist + 1, pre_e,
                                           inorder, root_idx+1, in_e);
    TreeNode* root = new TreeNode(root_val);
    root->left = left;
    root->right = right;
    return root;
}

void test() {
    int A[] = {1, 2, 3, 4};
    int B[] = {1, 2, 3, 4};

    std::vector<int> pre(A, A + sizeof(A)/sizeof(int));
    std::vector<int> in(B, B + sizeof(B)/sizeof(int));
    TreeNode* root = buildTree(pre, in);
}

int main() {
    test();
}
