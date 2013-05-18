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
    ListNode *swapPairs(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* before_head = new ListNode(0);
        before_head->next = head;
        ListNode* prev = before_head;
        
        while (prev != NULL) {
            ListNode* tail = advance_list(prev, 2);
            if (tail == NULL) {
                break;
            }
            ListNode* next = tail->next;
            ListNode* tmp = prev->next;
            tail->next = tmp;
            tmp->next = next;
            prev->next = tail;
            prev = tmp;
        }
        return before_head->next;
    }
    
    ListNode* advance_list(ListNode* before_head, int k) {
        while (before_head && k-- > 0) {
            before_head = before_head->next;
        }
        return before_head;
    }
};
