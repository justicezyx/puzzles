#include "common.h"
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSymmetric(TreeNode *root) {
    if(root == NULL) {
        return true;
    }
    stack<pair<TreeNode *,TreeNode *> > s;
    s.push(make_pair(root->left,root->right));
    while(!s.empty()) {
        pair<TreeNode *,TreeNode *> cur = s.top();
        s.pop();
        if(cur.first == NULL && cur.second == NULL)
           continue;
        else if(cur.first == NULL || cur.second == NULL || cur.first->val != cur.second->val)
          return false;
        else
        {
            s.push(make_pair(cur.first->left,cur.second->right));
            s.push(make_pair(cur.first->right,cur.second->left));
        }
    }
    return true;
}

void test() {
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(1);
    root->left = left;
    print(isSymmetric(root));
}

int main() {
    test();
}

