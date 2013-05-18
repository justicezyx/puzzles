/**
 * Definition for singly-linked list.
 */
#include "common.h"
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
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
    ListNode *reverseKGroup(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* before_head = new ListNode(0);
        before_head->next = head;
        
        for (ListNode* prev = before_head; prev != NULL; ) {
            pair<ListNode*, ListNode*> beg_end = get_next_k(prev, k);
            if (beg_end.second == NULL) {
                break;
            }
            ListNode* new_tail = reverse(beg_end.first, beg_end.second);
            prev = new_tail;
        }
        return before_head->next;
    }
    
    ListNode* reverse(ListNode* before_head, ListNode* last) {
        ListNode* new_head = last;
        ListNode* new_tail = before_head->next;
        ListNode* next = last->next;
        for (ListNode* prev = before_head->next, *cur = prev->next; prev != last; ) {
            // ListNode* cur = prev->next;
            ListNode* tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        before_head->next = new_head;
        new_tail->next = next;
        return new_tail;
    }
    
    // return the next k nodes, not including prev.
    pair<ListNode*,ListNode*> get_next_k(ListNode* prev, int k) {
        ListNode* cur = prev->next;
        int i = 0;
        while (cur && i < k-1) {
            cur = cur->next;
            ++i;
        }
        return make_pair(prev, cur);
    }
};

int main() {
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    n1->next = n2;
    n2->next = n3;

    Solution sol;
    sol.reverseKGroup(n1, 3);
}
