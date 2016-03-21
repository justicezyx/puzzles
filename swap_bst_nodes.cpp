/**
 * Two elements of a binary search tree (BST) are swapped by mistake.
 *
 * Recover the tree without changing its structure.
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
#include "common.h"
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
    void proc(TreeNode *root, TreeNode *&n1, TreeNode *&n2, TreeNode *&prev)
    {
        if(!root)
            return;
        proc(root->left,n1,n2,prev);
        if(prev && prev->val > root->val)
        {
            n2 = root;
            if(!n1)
                n1 = prev;
        }
        prev = root;
        proc(root->right,n1,n2,prev);
    }
    void recoverTree(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        TreeNode *n1 = NULL;
        TreeNode *n2 = NULL;
        TreeNode *prev = NULL;
        proc(root,n1,n2,prev);
        if(n1 && n2)
            swap(n1->val,n2->val);
    }
};

void test() {
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(2);
    root->left = left;

    Solution solution;
    solution.recoverTree(root);
}

int main() {
    test();
}
