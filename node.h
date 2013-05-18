#ifndef NODE_H
#define NODE_H

struct node {
    int data;
    node* left;
    node* right;
    node* parent;
    node(int v) : data(v), left(NULL), right(NULL), parent(NULL) { }
};

#endif
