#include "common.h"

struct ListNode {
    ListNode* next;
    int data;
    ListNode(int v) : data(v), next(NULL) { }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL || head->next == NULL) { return head; }
        
        ListNode* cur = head;
        ListNode* prev = NULL;
        for (int i = 1; i < m && cur != NULL; ++i) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == NULL) { return head; }
        
        ListNode* sub_tail = cur;
        ListNode* sub_prev = prev;
        ListNode* next = cur->next;
        for (int i = m; i < n && next != NULL; ++i) {
            ListNode* tmp = next->next;
            next->next = cur;
            cur = next;
            next = tmp;
        }
        sub_tail->next = next;
        if (sub_prev != NULL) {
            sub_prev->next = cur;
            return head;
        } else {
            return cur;
        } 
    }
};

void print_list(ListNode* head) {
    if (head != NULL) {
        std::cout<<"Head:"<<head->data<<std::endl;
    }
    while (head != NULL) {
        std::cout<<head->data<<" ";
        head = head->next;
    }
}

void test() {
    ListNode* head = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    head->next = n2;
    n2->next = n3;
    n3->next = n4;

    print_list(head);
    reverseBetween(head, 2, 3);
    std::cout<<"Head:"<<head->data<<std::endl;
    print_list(head);    
}

int main() {
    test();
}
