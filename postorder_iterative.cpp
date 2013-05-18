#include "common.h"
#include "node.h"

std::vector<int> postorder_iterative(node* root) {
    std::vector<int> res;
    if (root == NULL) {
        return res;
    }

    node* prev = NULL;
    std::stack<node*> h;
    h.push(root);

    bool left_done = false;
    while (!h.empty()) {
        std::cout<<"stack size:"<<h.size()<<std::endl;
        node* cur = h.top();
        if (cur->left == prev || cur->left == NULL) {
            std::cout<<"left is done"<<std::endl;
            left_done = true;
            h.pop();
            res.push_back(cur->data);
            prev = cur;
            if (cur->right != NULL) {
                std::cout<<"push right of "<<cur->data<<std::endl;
                h.push(cur->right);
            }
        } else if (left_done && (cur->right == prev || cur->right == NULL)) {
            std::cout<<"right is done"<<std::endl;
            res.push_back(cur->data);
            h.pop();
            prev = cur;
        } else {
            std::cout<<"push left of "<<cur->data<<std::endl;
            h.push(cur->left);
        }
    }
}

int main() {
    node* root = new node(0);
    node* left = new node(-1);
    node* right = new node(1);
    root->left = left;
    left->left = right;
    std::vector<int> res = postorder_iterative(root);
    print(res.begin(), res.end());
}
