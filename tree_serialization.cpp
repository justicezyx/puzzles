#include "common/common.h"

struct tree_node {
    int id;
    int data;
    std::list<tree_node*> d;
    
    tree_node(int i, int v) : id(i), data(v), d() { }
};

void serialize_recurrsive(tree_node* root, std::string& res);

std::string serialize(tree_node* root) {
    std::string res;
    serialize_recurrsive(root, res);
    return res;
}

void serialize_recurrsive(tree_node* root, std::string& res) {
    if (!root) { return; }
    res.push_back('(');
    std::ostringstream oss;
    oss<<root->id;
    oss<<":";
    oss<<root->data;
    res += oss.str();
    
    typedef std::list<tree_node*>::iterator itor;
    for (itor i = root->d.begin(); i != root->d.end(); ++i) {
        serialize_recurrsive(*i, res);
    }
    res.push_back(')');
}

struct node {
    tree_node* n;
};

tree_node* deserialize(const std::string& s) {
    if (s.size() <= 2) {
        // at lease has ( and ) and others.
        return NULL;
    }

    std::stack<node> h;
    
    assert(s[0] == '(');
    for (int i = 0; i < s.size(); ) {
        std::cout<<"current char:"<<s[i]<<std::endl;

        if (s[i] == '(') {
            ++i;
            /*
            node n;
            n.n = NULL;
            h.push(n);
            ++i;
            */
        } else if (s[i] == ')') {
            // pop all node.
            std::cout<<"Poping all nodes:"<<h.size()<<std::endl;
            node n = h.top();
            h.pop();
            // h.pop();
            
            if (h.empty()) {
                return n.n;
            } else {
                h.top().n->d.push_back(n.n);
            }
            ++i;
        } else {
            int b = i;
            while (s[++i] != ':') { }
            std::istringstream iss(s.substr(b, i - b));
            int id; iss >> id;
            b = i + 1;

            while (s[++i] != ')' && s[i] != '(') { }
            std::istringstream iss2(s.substr(b, i - b));
            int data; iss2 >> data;
            std::cout<<"data: "<<data<<std::endl;

            node n;
            n.n = new tree_node(id, data);
            h.push(n);
        }
    }
}

void test() {
    tree_node* root = new tree_node(0, 1);
    tree_node* left = new tree_node(1, 1);
    tree_node* right = new tree_node(2, 1);
    tree_node* three = new tree_node(3, 1);
    tree_node* n4 = new tree_node(4, 1);
    tree_node* n5 = new tree_node(5, 1);
    root->d.push_back(left);
    root->d.push_back(right);
    root->d.push_back(three);
    left->d.push_back(n4);
    left->d.push_back(n5);

    std::string res = serialize(root);
    std::cout<<res<<std::endl;
    
    root = deserialize(res);
    std::cout<<"Root:"<<root->id<<" "<<root->data<<std::endl;
    std::cout<<"Root children:"<<root->d.size()<<std::endl;
    std::cout<<"root's first child:"<<root->d.front()->id<<std::endl;
    std::cout<<"root's first child's children:"<<root->d.front()->d.size()<<std::endl;
}

int main() {
    test();
}
