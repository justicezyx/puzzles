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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* before_head = new ListNode(0);
        before_head->next = head;
        
        ListNode* cur = before_head;
        int i = 0;
        while (i++ < n && cur) {
            cur = cur->next;
        }
        ListNode* res;
        if (cur == NULL) {
            res = head;
        }
        ListNode* prev = before_head;
        while (cur->next != NULL) {
            cur = cur->next;
            prev = prev->next;
        }
        // return res;
        ListNode* tmp = prev->next;
        prev->next = tmp->next;
        // delete tmp;
        res = before_head->next;
        // delete before_head;
        return res;
    }
};
