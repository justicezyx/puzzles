#include "common.h"
using namespace std;

struct node {
    node* left;
    node* right;
    node* parent;
    int data;
    node(int v) : data(v), left(NULL), right(NULL), parent(NULL) { }
};

vector<node*> inorder(node* root) {
    vector<node*> res;
    if (root == NULL) {
        return res;
    }
    node* prev = NULL;
    node* cur = root;
    while (cur) {
        if (cur->right == prev && prev != NULL) {
            prev = cur;
            cur = cur->parent;
        } else if ((cur->left == prev && prev != NULL) || cur->left == NULL) {
            res.push_back(cur);
            prev = cur;
            if (cur->right) {
                cur = cur->right;
            } else {
                cur = cur->parent;
            }
        } else if (cur->left != NULL) {
            while (cur->left != NULL) {
                cur = cur->left;
            }
        }    
    }
    return res;
}

int main() {
    node* root = new node(0);
    node* left = new node(-1);
    node* right = new node(1);
    root->right = left;
    left->right = right;
    left->parent = root;
    right->parent = left;

    vector<node*> res = inorder(root);
    for (int i = 0; i < res.size(); ++i) {
        cout<<res[i]->data<<(i == res.size() ? "\n" : " ");
    }
}

