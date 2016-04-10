#include <iostream>
#include <stack>

#include "node.h"

typedef void (*visit)(node* node);

void print(node* node) {
    if (node == NULL) {
        std::cout<<"NULL ";
    } else {
        std::cout<<node->val<<" ";
    }
}

void pre_order_recur(node* root, visit f) {
    if (root == NULL) { return; }
    
    // do something with root.
    f(root);
    
    pre_order_recur(root->left, f);
    pre_order_recur(root->right, f);
}

void pre_order_iterative(node* root, visit f) {
    std::stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node* cur = s.top();
        s.pop();
        // do something with cur.
        f(cur);
        
        if (cur->left != NULL) s.push(cur->left);
        if (cur->right != NULL) s.push(cur->right);
    }
}

void in_order_recursive(node* root, visit f) {
    if (root == NULL) { return; }
    
    in_order_recursive(root->left, f);
    f(root);
    in_order_recursive(root->right, f);
}
    
void in_order_iterative(node* root, visit f) {
    if (root == NULL) { return; }

    std::stack<node*> s;
    s.push(root);
    node* prev = root;

    while (!s.empty()) {
        node* cur = s.top();
        if (prev == cur->right && cur->right != NULL) {
            // if cur->right == NULL, it's not clear if right is finished.
            s.pop();
            prev = cur;
        } else if ((prev == cur->left && cur->left != NULL) || cur->left == NULL) {
            f(cur);
            if (cur->right != NULL) {
                s.push(cur->right);
            } else {
                s.pop();
                prev = cur;
            }
        } else {
            // left not finished, just push; it wont be NULL since it is eliminated
            // in the cur->left == NULL checking.
            s.push(cur->left);
        }
    }
}

void post_order_recursive(node* root, visit f) {
    if (root == NULL) { return; }

    if (root->left != NULL) post_order_recursive(root->left, f);
    if (root->right != NULL) post_order_recursive(root->right, f);
    f (root);
}

int post_order_iterative(node* root, visit f) {
    if (root == NULL) { return 0; }

    std::stack<node*> s;
    std::stack<int> ms;
    s.push(root);

    int max = std::max(root->val, 0);
    node* prev = NULL;
    while (!s.empty()) {
        node* cur = s.top();
        int ml = 0; 
        int mr = 0;
        
        if (cur->right == prev && prev != NULL) {
            // right branch traversed; put in right branch.
            s.pop();
            f(cur);
            prev = cur;

            if (cur->right != NULL) { mr = std::max(ms.top(), 0); ms.pop(); }
            if (cur->left != NULL) { ml = std::max(ms.top(), 0); ms.pop(); }
            max = std::max(max, cur->val + mr + ml);
            ms.push(cur->val + std::max(ml, mr));
        } else if (cur->left == NULL || cur->left == prev) {
            // left branch traversed; put in right branch.
            if (cur->right != NULL) {
                s.push(cur->right);
            } else {
                s.pop();
                f(cur);
                prev = cur;

                if (cur->right != NULL) { mr = std::max(ms.top(), 0); ms.pop(); }
                if (cur->left != NULL) { ml = std::max(ms.top(), 0); ms.pop(); }
                max = std::max(max, cur->val + mr + ml);
                ms.push(cur->val + std::max(ml, mr));
            }
        } else {
            // this branch is not traversed yet.
            s.push(cur->left);
        }
    }

    return max;
}

node* node0 = new node(0);
node* node1 = new node(2);
node* node2 = new node(2);
node* node3 = new node(3);
node* node4 = new node(10);
node* node5 = new node(1);
node* node6 = new node(3);

void test() {
    node0->left = node1;
    node0->right = node2;

    node1->left = node3;
    node1->right = node4;

    node2->left = node5;
    node2->right = node6;

    post_order_recursive(node0, print);
    std::cout<<std::endl;
    std::cout<<post_order_iterative(node0, print);
}

int main() {
    test();
}
