#include "common.h"
using namespace std;

struct tree_node {
    int data;
    list<tree_node*> d;
    tree_node(int v) : data(v), d() { }
};

ostream& operator<<(ostream& out, tree_node* root) {
    if (root == NULL) {
        return out;
    }
    out<<"(";
    out<<root->data;
    for (list<tree_node*>::iterator i = root->d.begin();
            i != root->d.end(); ++i) {
        out<<*i;
    }
    out<<")";
    return out;
}

istream& operator>>(istream& in, tree_node& node) {
    stack<tree_node*> h;
    char c;
    in >> c;
    in >> node.data;
    h.push(&node);
    
    while (in >> c) {
        if (c == '(') {
            int data;
            in >> data;
            tree_node* n = new tree_node(data);
            h.push(n);
        } else if (c == ')') {
            tree_node* n = h.top();
            h.pop();
            if (h.empty()) {
                break;
            }
            h.top()->d.push_back(n);
        }
    }
    return in;
}

int main() {
    tree_node* root = new tree_node(0);
    tree_node* left = new tree_node(1);
    tree_node* right = new tree_node(2);
    tree_node* three = new tree_node(3);
    tree_node* n4 = new tree_node(4);
    tree_node* n5 = new tree_node(5);
    root->d.push_back(left);
    root->d.push_back(right);
    root->d.push_back(three);
    left->d.push_back(n4);
    left->d.push_back(n5);
    ostringstream oss;
    oss << root << endl;
    cout<<oss.str();
    
    istringstream iss(oss.str());
    tree_node node(0);
    iss >> node;
    
    cout << &node << endl;
}
        
