#include <iostream>
#include <vector>
#include <cassert>

struct node {
    int data;
    node* left;
    node* right;
    node* parent;

    node(int d) {
        data = d;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

node* left_most(node* n);

node* inorder_successor(node* n) {
    if (n == NULL) {
        return NULL;
    }

    if (n != NULL && n->right != NULL) {
        return left_most(n->right);
    }

    // go upper.
    node* c = n;
    node* p = c->parent;
    while (p != NULL && c != p->left) {
        c = p;
        p = c->parent;
    }
    return p;
}

node* left_most(node* n) {
    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}

/*
 *        0
 *    -5     5
 *   -7 -4  4 6
 */
void test() {
    std::vector<node*> nodes;
    node* root = new node(0);
    nodes.push_back(root);

    node* n_minus5 = new node(-5);
    nodes.push_back(n_minus5);

    node* n_minus7 = new node(-7);
    nodes.push_back(n_minus7);

    node* n_minus4 = new node(-4);
    nodes.push_back(n_minus4);

    node* n5 = new node(5);
    nodes.push_back(n5);

    node* n4 = new node(4);
    nodes.push_back(n4);

    node* n6 = new node(6);
    nodes.push_back(n6);

    root->left = n_minus5;
    root->right = n5;
    n_minus5->parent = root;
    n5->parent = root;
    
    n_minus5->left = n_minus7;
    n_minus5->right = n_minus4;
    n_minus7->parent = n_minus5;
    n_minus4->parent = n_minus5;

    n5->left = n4;
    n5->right = n6;
    n4->parent = n5;
    n6->parent = n5;

    for (int i = 0; i < nodes.size() - 1; i++) {
        std::cout<<nodes[i]->data<<" "<<inorder_successor(nodes[i])->data<<std::endl;
    }

    assert(inorder_successor(nodes.back()) == NULL);
}

int main() {
    test();
}
