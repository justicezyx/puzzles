/**
 * Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 *
 * For example:noh
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
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
    ListNode *deleteDuplicates(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* before_head = new ListNode(0);
        before_head->next = head;
        ListNode* prev = before_head;
        while (head) {
            ListNode* tmp = head->next;
            while (tmp && tmp->val == head->val) {
                tmp = tmp->next;
            }
            if (head->next == tmp) {
                prev->next = head;
                prev = head;
                head = tmp;
            } else {
                prev->next = tmp;
                head = tmp;
            }
        }
        return before_head->next;;
    }
};
