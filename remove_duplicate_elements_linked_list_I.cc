/**
 * Remove Duplicates from Sorted ListApr 22 '12917 / 1704
 * Given a sorted linked list, delete all duplicates such that each element appear only once.
 *
 * For example:noh
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
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
        ListNode* res = head;
        while (head) {
            ListNode* tmp = head->next;
            while (tmp && tmp->val == head->val) {
                tmp = tmp->next;
            }
            head->next = tmp;
            head = tmp;
        }
        return res;
    }
};

