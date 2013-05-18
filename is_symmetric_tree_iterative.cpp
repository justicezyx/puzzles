#include "common.h"
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSymmetric(TreeNode* root) {
    stack<TreeNode*> lhs;
    int l_num = 0;
    for (TreeNode* l_root = root; l_root != NULL; l_root = l_root->left) {
        ++l_num;
        lhs.push(l_root);
    }
    
    stack<TreeNode*> rhs;
    int r_num = 0;
    for (TreeNode* r_root = root; r_root != NULL; r_root = r_root->right) {
        ++r_num;
        rhs.push(r_root);
    }
    if (l_num != r_num) {
        return false;
    }
    
    while (!lhs.empty() && !rhs.empty()) {
        TreeNode* l_cur = lhs.top();
        lhs.pop();
        
        TreeNode* r_cur = rhs.top();
        rhs.pop();
        
        if ((l_cur == NULL && r_cur != NULL) 
            || (l_cur != NULL && r_cur == NULL)) {
            return false;
        }
        if (l_cur->val != r_cur->val) {
            return false;
        }
        
        int l_num = 0;
        for (l_cur = l_cur->right; l_cur != NULL; l_cur = l_cur->left) {
            ++l_num;
            lhs.push(l_cur);
        }
        int r_num = 0;
        for (r_cur = r_cur->left; r_cur != NULL; r_cur = r_cur->right) {
            ++r_num;
            rhs.push(r_cur);
        }
        if (l_num != r_num) {
            return false;
        }
    }
    return lhs.empty() && rhs.empty();
}

int main() {
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(1);
    root->left = left;
    std::cout<<isSymmetric(root)<<std::endl;
}

