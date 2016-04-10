Node {
    Node left;
    Node right;
    Node parent;
}


Node inorderSuccessor(Node n)
{
    ...
}



inorder(Node n) {
    if (n != null) {
        inorder(n.left);
        visit(n);
        inorder(n.right);
    }
}

Node inorderSuccessor(Node n)
{
    if (n == NULL) { return NULL; }
    
    // if n has right child
    if (n->right != NULL) {
        // return the left most child of n->right;
        Node tmp = n->right;
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        return tmp;
    }
    
    if (n->parent == NULL) {
        return NULL;
    }
    
    if (n == n->parent->left) {
        return n->parent;
    }
    
    if (n == n->parent->right) {
        // n is the right node of parent.
        Node tmp = n->parent;
        while (tmp != NULL && tmp->parent != NULL && tmp != tmp->parent->left) {
            tmp = tmp->parent;
        }
        if (tmp == NULL) { return NULL; }
        return tmp->parent;
    }
}

nterval {
    long start;
    long end;
}

input:
(30, 50)
(70, 100)
(10, 20)
(40, 60)
(80, 90)


output:
(10, 20)
(30, 60)
(70, 100)

bool compare(Interval lhs, Interval rhs) {
    return lhs.begin < rhs.begin;
}
    
vector<Interval> merge_interval(vector<Interval>& intervals) {
    // TODO need input validation code in production.
    
    vector<Interval> res;
    if (intervals.empty()) { return res; }
    
    sort(intervals.begin(), intervals.end(), compare);
    for (int i = 0; i < intervals.size(); ) {
        long cur_begin = intervals[i].begin;
        long cur_end = intervals[i].end;
        int j = i + 1;
        long new_end = cur_end;
        while (j < intervals.size() && intervals[j].begin <= new_end) {
            new_end = max(new_end, intervals[j].end);
            ++j;
        }
        res.push_back(Interval(cur_begin, new_end));
        i = j;
    }
    return res;
}

1. emtpy input
2. all non overlapping input
3. two overlapped input
4. all random input
5. intervals complete inside another one
5. input validations
