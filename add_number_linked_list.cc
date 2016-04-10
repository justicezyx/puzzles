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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode* before_head = new ListNode(0);
        ListNode* prev = before_head;
        
        int carry = 0;
        while (carry || l1 || l2) {
            int v = carry + (l1? l1->val : 0) + (l2 ? l2->val : 0);
            prev->next = new ListNode(v % 10);
            carry = v / 10;
            prev = prev->next;
            l1 = !l1 ? l1 : l1->next;
            l2 = !l2 ? l2 : l2->next;
        }
        ListNode* res = before_head->next;
        delete before_head;
        return res;
    }
};
