#include "common.h"
using namespace std;

struct list_node {
    list_node* next;
    int data;
    list_node(int v) {
        next = NULL;
        data = v;
    }
};

list_node* advance_list(list_node* head, int dist) {
    int i = 0;
    while (head && i++ < dist) {
        head = head->next;
    }
    return head;
}

pair<list_node*,list_node*> merge_fixed_length(list_node* h1, list_node* h2, int len) {
    if (h1 == NULL) {
        return make_pair(h2, advance_list(h2, len - 1));
    } else if (h2 == NULL) {
        return make_pair(h1, advance_list(h1, len - 1));
    }
    
    list_node* before_head = new list_node(0);
    list_node* prev = before_head;
    int len1 = 0;
    int len2 = 0;

    while (len1 < len && len2 < len && h1 && h2) {
        if (h1->data < h2->data) {
            ++len1;
            prev->next = h1;
            prev = h1;
            h1 = h1->next;
        } else {
            ++len2;
            prev->next = h2;
            prev = h2;
            h2 = h2->next;
        }
    }
    
    list_node* tail = prev;
    if (h1 && len1 < len) {
        prev->next = h1;
        tail = advance_list(tail, len - len1);
    } else if (h2 && len2 < len) {
        prev->next = h2;
        tail = advance_list(tail, len - len2);
    }
    return make_pair(before_head->next, tail);
}    

list_node* merge_sort(list_node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    list_node* before_head = new list_node(0);
    before_head->next = head;
    for (int len = 1; ; len <<= 1) {
        // starting from head, merge the 2 consecutive sublists whose length is "len".
        list_node* prev = before_head;
        list_node* cur = before_head->next;
        int count = 0;
        while (cur != NULL) {
            ++count;
            list_node* h1 = cur;
            list_node* h2 = advance_list(h1, len);
            cur = advance_list(h2, len);

            pair<list_node*, list_node*> sublist = merge_fixed_length(h1, h2, len);
            prev->next = sublist.first;
            if (sublist.second != NULL) {
                sublist.second->next = cur;
            }
            prev = sublist.second;
        }
        if (count <= 1) { break; }
    }
    return before_head->next;
}

void test_advance_list() {
    list_node* n0 = new list_node(1);
    list_node* n1 = new list_node(2);
    list_node* n2 = new list_node(3);
    n0->next = n1;
    n1->next = n2;

    cout<<advance_list(n0, 0)->data<<std::endl;
    cout<<advance_list(n0, 1)->data<<std::endl;
    cout<<advance_list(n1, 1)->data<<std::endl;
    cout<<advance_list(n0, 2)->data<<std::endl;
}
    
void test_merge_fixed_length() {
    list_node* n0 = new list_node(1);
    list_node* n1 = new list_node(2);
    list_node* n2 = new list_node(0);
    list_node* n3 = new list_node(5);
    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    pair<list_node*, list_node*> new_list = merge_fixed_length(n0, n2, 2);

    std::cout<<new_list.first->data<<std::endl;
    std::cout<<new_list.second->data<<std::endl;
}

void test_merge_sort() {
    list_node* n0 = new list_node(3);
    list_node* n1 = new list_node(0);
    list_node* n2 = new list_node(1);
    list_node* n3 = new list_node(0);
    list_node* n4 = new list_node(-1);
    list_node* n5 = new list_node(-2);
    list_node* n6 = new list_node(-3);
    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;

    list_node* head = merge_sort(n0);
    while (head) {
        std::cout<<head->data<<(head->next == NULL ? "\n" : " ");
        head = head->next;
    }
}

int main() {
    test_merge_sort();
}

    
