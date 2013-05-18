#include "common.h"

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int v;
    TreeNode(int data) {
        left = NULL;
        right = NULL;
        v = data;
    }
};

std::pair<TreeNode*,TreeNode*> helper(TreeNode* root) {
    if (root == NULL) { return std::make_pair((TreeNode*)NULL, (TreeNode*)NULL); }
    std::cout<<"Node:"<<root->v<<std::endl;

    std::pair<TreeNode*,TreeNode*> l = helper(root->left);
    std::pair<TreeNode*,TreeNode*> r = helper(root->right);
    root->left = NULL;

    if (l.first == NULL && r.first == NULL) {
        return std::make_pair(root, root);
    }
    if (l.first == NULL && r.first != NULL) {
        root->right = r.first;
        return std::make_pair(root, r.second);
    }
    if (l.first != NULL && r.first == NULL) {
        root->right = l.first;
        return std::make_pair(root, l.second);
    }
    if (l.first != NULL && r.first != NULL) {
        root->right = l.first;
        l.second->right = r.first;
        return std::make_pair(root, r.second);
    }
}

void test() {
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    n1->left = n2;
    n2->right = n3;
    std::cout<<n1->left<<std::endl;
    helper(n1);
    std::cout<<n1->left<<std::endl;
}

int main() {
    test();
}
