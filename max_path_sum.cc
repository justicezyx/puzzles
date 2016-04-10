#include <iostream>

struct node {
    node* left;
    node* right;
    int val;

    node(int v) : val(v), left(NULL), right(NULL) { }
};

int global_max = -1;

int max_path_sum(node* root) {
    // return the max sum path ends at root (inclusive).
    // update the global max sum.
    if (root == NULL) { return 0; }
    
    int ml = max_path_sum(root->left);
    int mr = max_path_sum(root->right);

    int res = std::max(root->val, root->val + std::max(ml, mr));
    
    int ms_l = std::max(0, ml);
    int ms_r = std::max(0, mr);

    global_max = std::max(ms_l + ms_r + root->val, global_max);

    return res;
}

void test() {
    node* node0 = new node(1);
    node* node1 = new node(2);
    node* node2 = new node(3);

    node0->left = node1;
    node0->right = node2;

    std::cout<<"max sum path: "<<max_path_sum(node0)<<std::endl;
    std::cout<<"global max sum: "<<global_max<<std::endl;
}

int main() {
    test();
}

