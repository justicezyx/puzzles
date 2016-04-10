#include <string>
#include <vector>

#include "common/common.h"

struct item {
    int id;
    double prob;

    item(int i, double p) {
        id = i;
        prob = p;
    }
};

struct node {
    item* real;
    node* l;
    node* r;
    
    node(item* i, node* lhs, node* rhs) {
        real = i;
        l = lhs;
        r = rhs;
    }

    ~node() {
        std::cout<<real->id<<std::endl;
        delete real;
        delete l;
        delete r;
    }
};

item* combine(item* a, item* b) {
    return new item(-1, a->prob + b->prob);
}
    
node* make_parent(node* a, node* b) {
    return new node(combine(a->real, b->real), a, b);
}
    
bool comp(node* lhs, node* rhs) {
    return lhs->real->prob >= rhs->real->prob;
}

void dfs(node* root, std::string& tmp, std::vector<std::string>& res) {
    if (root == NULL) return;
    if (root->l == NULL && root->r == NULL) {
        int i = root->real->id;
        res[i] = tmp;
        return;
    }
    tmp.push_back('0');
    dfs(root->l, tmp, res);
    tmp.resize(tmp.size()-1);

    tmp.push_back('1');
    dfs(root->r, tmp, res);
    tmp.resize(tmp.size()-1);
}

node* pop_heap(std::vector<node*>& v) {
    std::pop_heap(v.begin(), v.end(), comp);
    node* res = v.back();
    v.pop_back();
    return res;
}

std::vector<std::string> make_huffman(double* probs, int l) {
    std::vector<node*> helper;
    helper.reserve(l);

    for (int i = 0; i < l; i++) {
        item* itm = new item(i, probs[i]);
        node* n = new node(itm, NULL, NULL);
        helper.push_back(n);
    }

    std::make_heap(helper.begin(), helper.end(), comp);
    for (int i = 0; i < l - 1; i++) {
        node* a = pop_heap(helper);
        node* b = pop_heap(helper);
        node* ab = make_parent(a, b);
        helper.push_back(ab);
        std::push_heap(helper.begin(), helper.end(), comp);
    }

    std::vector<std::string> res(l);
    std::string tmp;
    dfs(helper.front(), tmp, res);
    delete helper.front();

    return res;
}

void test() {
    double probs[] = {0.1, 0.1, 0.1, 0.1, 0.1};
    int l = sizeof(probs) / sizeof(double);
    std::vector<std::string> codes = make_huffman(probs, l);
    print(codes.begin(), codes.end());
}

int main() {
    test();
}
