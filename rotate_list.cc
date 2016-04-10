/**
 * Rotate ListMar 28 '12865 / 2806
 * Given a list, rotate the list to the right by k places, where k is non-negative.
 *
 * For example:
 * Given 1->2->3->4->5->NULL and k = 2:noh
 * return 4->5->1->2->3->NULL.
 */
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
    ListNode *rotateRight(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (k <= 0 || head == NULL) {
            return head;
        }
        
        ListNode* cur = head;
        
        int i = 0;
        for ( ; cur != NULL && i < k-1; ++i) {
            cur = cur->next;
        }
        if (cur == NULL) {
            // k is larger than list length.
            return rotateRight(head, k - i);
        }
        
        ListNode* before_head = new ListNode(0);
        before_head->next = head;
        
        ListNode* prev = before_head;
        while (cur->next != NULL) {
            prev = prev->next;
            cur = cur->next;
        }
        delete before_head;
        
        if (prev == before_head) {
            // k is same as list length.
            return head;
        }
        
        cur->next = head;
        head = prev->next;
        
        prev->next = NULL;
        
        return head;
    }
};

