#include <iostream>

struct node {
    node* next;
    int val;
    node(int v) {
        val = v;
        next = NULL;
    }
};

node* insert(node* l, int val) {
    if (l == NULL) {
        l = new node(val);
        l->next = l;
        return l;
    }

    node* c = l;
    node* n = new node(val);
    
    while (c->next != l) {
        if (val >= c->val && val <= c->next->val) {
            break;
        }
        if (c->val > c->next->val && (val >= c->val || val <= c->next->val)) {
            // the largest one and the smallest one.
            break;
        }
        c = c->next;
    }

    n->next = c->next;
    c->next = n;
    return n;
}
        
void test() {
    node* node0 = new node(0);
    node* node1 = new node(1);
    node* node2 = new node(2);
    node* node3 = new node(3);
    node* node4 = new node(4);

    node0->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node0;

    
    node* node5 = new node(5);
    node* node6 = new node(5);
    node5->next = node6;
    node6->next = node5;

    node* n = insert(node1, -1);
    std::cout<<(n->next == node0)<<std::endl;
}

int main() {
    test();
}
