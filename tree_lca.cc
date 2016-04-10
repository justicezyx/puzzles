#include "common/common.h"
#include "node.h"

bool dfs(node* root, node* n, std::list<node*>& path) {
    if (!root || !n) {
        return false;
    }

    if (root == n) {
        return true;
    }

    path.push_back(root->left);
    if (dfs(root->left, n, path)) {
        return true;
    }
    path.pop_back();

    path.push_back(root->right);
    if (dfs(root->right, n, path)) {
        return true;
    }
    path.pop_back();

    return false;
}

std::list<node*> dfs_search(node* root, node* n) {
    std::list<node*> res;
    if (!root || !n) {
        return res;
    }

    res.push_back(root);
    dfs(root, n, res);
    return res;
}
        
node* lca(node* root, node* a, node* b) {
    if (!root || !a || !b) {
        // all must be valid node.
        return NULL;
    }

    std::list<node*> patha = dfs_search(root, a);
    std::list<node*> pathb = dfs_search(root, b);

    typedef std::list<node*>::iterator itor;
    itor res;
    for (itor ia = patha.begin(), ib = pathb.begin();
           ia != patha.end() && ib != pathb.end() && *ia == *ib;
           ++ia, ++ib) {
        res = ia;
    }

    return *res;
}

node* lca_recur(node* root, node* a, node* b) {
    if (!root) {
        return NULL;
    }

    std::cout<<"node:"<<root->data<<" ";
    if (root == a || root == b) {
        return root;
    }
    
    node* l = lca_recur(root->left, a, b);
    node* r = lca_recur(root->right, a, b);

    if (l && r) {
        return root;
    }
    if (l) { return l; }
    if (r) { return r; }
    return NULL;
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

    std::list<node*> path = dfs_search(root, n6);
    for (std::list<node*>::iterator i = path.begin();
         i != path.end();
         ++i) {
        std::cout<<(*i)->data<<" ";
    }

    std::cout<<lca(root, n_minus5, n6)->data<<std::endl;
    node* lca = lca_recur(root, n_minus5, n6);
    std::cout<<lca_recur(root, n_minus5, n6)->data<<std::endl;
    std::cout<<std::endl;
}

int main() {
    test();
}


