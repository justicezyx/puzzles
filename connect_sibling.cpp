#include <iostream>

struct node {
    node* left;
    node* right;
    node* sibling;
    int data;

    node(int v) {
        left = NULL;
        right = NULL;
        sibling = NULL;
        data = v;
    }

    node(int v, node* left, node* right) {
        left = left;
        right = right;
        sibling = NULL;
        data = v;
    }

    ~node() {
        delete left;
        delete right;
    }
};

void connect_sibling(node* root) {
    node* cur = root;
    while (cur != NULL) {
        // find the starting point of the next level.
        node* next_level_start = NULL;
        while (cur != NULL) {
            if (cur->left != NULL) {
                next_level_start = cur->left;
                break;
            } else if (cur->right != NULL) {
                next_level_start = cur->right;
                break;
            }
            cur = cur->sibling;
        }
            
        for (node* prev = NULL; cur != NULL; cur = cur->sibling) {
            if (cur->left != NULL) {
                if (prev != NULL) {
                    prev->sibling = cur->left;
                }
                prev = cur->left;
            }
            
            if (cur->right != NULL) {
                if (prev != NULL) {
                    prev->sibling = cur->right;
                } 
                prev = cur->right;
            }
        }
        cur = next_level_start;    
    }
}

void test() {
    node* n0 = new node(0);
    node* n1 = new node(1);
    node* n2 = new node(2);

    n0->left = n1;
    n0->right = n2;

    connect_sibling(n0);

    for (node* n = n1; n != NULL; n = n->sibling) {
        std::cout<<n->data<<" ";
    }
}

int main() {
    test();
}

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        TreeLinkNode* cur = root;
        while (cur != NULL) {
            TreeLinkNode* cur_node = cur;
            TreeLinkNode* next_level_begin = NULL;
            TreeLinkNode* next_level_node = NULL;
            while (cur_node != NULL) {
                if (cur_node->left != NULL) {
                    if (next_level_begin == NULL) {
                        next_level_begin = cur_node->left;
                    }
                    if (next_level_node == NULL) {
                        next_level_node = cur_node->left;
                    } else {
                        next_level_node->next = cur_node->left;
                        next_level_node = cur_node->left;
                    }
                }
                
                if (cur_node->right != NULL) {
                    if (next_level_begin == NULL) {
                        next_level_begin = cur_node->right;
                    }
                    if (next_level_node == NULL) {
                        next_level_node = cur_node->right;
                        cur = cur_node->right;
                    } else {
                        next_level_node->next = cur_node->right;
                        next_level_node = cur_node->right;
                    }
                }
                cur_node = cur_node->next;
            }
            cur = next_level_begin;
        }
    }
};
